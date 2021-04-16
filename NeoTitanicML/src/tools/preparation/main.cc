#include <NeoML/NeoML.h>
#include <stdio.h>

#include <cxxopts.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include "model/data//preprocessing/standart_scaler.h"
#include "model/data/passenger_info_converter.h"
#include "tools/preparation/csv_reader.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::vector;
using namespace neotitanicml;
using namespace NeoML;

void PrintHelp(const cxxopts::Options& options) {
    cout << options.help() << endl;
}

cxxopts::ParseResult ParseArgs(int argc, char* argv[]) {
    cxxopts::Options options("preparation", "Prepare dataset for model learning");

    options.add_options()
        ("h,help", "Print usage")
        ("c,config", "Config (json)", cxxopts::value<string>())
        ("s,source", "Source data", cxxopts::value<string>())
        ("l,sep", "Separator in source scv-file", cxxopts::value<string>()->default_value("|"))
        ("n,features-count", "Number of featurs", cxxopts::value<int>()->default_value("7"))
        ("d,destination", "Destination - NeoML-Archive", cxxopts::value<string>())
    ;

    try {
        auto args = options.parse(argc, argv);

        if (args.count("help")) {
            PrintHelp(options);
            std::exit(0);
        }

        if ((!args.count("config")) ||
            (!args.count("source")) ||
            (!args.count("destination"))) {
            cerr << "ERROR: not define some arguments!"
                 << endl
                 << endl;
            PrintHelp(options);
            std::exit(1);
        }

        // check type correctness
        args["features-count"].as<int>();

        return args;

    } catch (std::exception& e) {
        cerr << "ERROR: " << e.what() << endl
             << endl;
        PrintHelp(options);
        std::exit(1);
    }
}

nlohmann::json ReadConfig(const string& config_file) {
    nlohmann::json config;

    try {
        std::ifstream config_file_stream(config_file);
        config = nlohmann::json::parse(config_file_stream);
        config_file_stream.close();
    } catch (nlohmann::detail::parse_error& pe) {
        cerr << "JSON_PARSER_ERROR: " << pe.what() << endl;
        std::exit(1);
    }

    return config;
}

unique_ptr<CsvReader> PrepareReader(const string& source_file, const string& sep) {
    auto reader = unique_ptr<CsvReader>(new CsvReader(source_file, sep));
    if (!reader->Init()) {
        cerr << "ERROR: Can't open file: " << source_file << endl;
        std::exit(1);
    }
    // skip first line (header)
    vector<string> fields;
    reader->Next(fields);
    return reader;
}

unique_ptr<PassengerInfoConverter> PrepareConverter(const nlohmann::json& config) {
    unique_ptr<PassengerInfoConverter> converter = PassengerInfoConverter::FromJson(config);
    if (!converter) {
        cerr << "ERROR: Can't configure converter: "
             << endl;
        std::exit(1);
    }

    return converter;
}

unique_ptr<StandartScaler> PrepareStdScaler(const nlohmann::json& config) {
    auto scaler = unique_ptr<StandartScaler>(new StandartScaler());

    try {
        auto mean = config["scaler-mean"].get<vector<float>>();
        auto std_deviation = config["scaler-std"].get<vector<float>>();
        if (!scaler->SetMeasures(mean, std_deviation)) {
            throw std::invalid_argument("bad mean and std");
        };
    } catch (std::exception& e) {
        cerr << "ERROR: Can't configure scaler: " << e.what() << endl;
        std::exit(1);
    }

    return scaler;
}

void StoreDataset(CPtr<CMemoryProblem> dataset, const string& path) {
    try {
        CArchiveFile archive_file(path.c_str(), CArchive::store);
        CArchive archive(&archive_file, CArchive::SD_Storing);

        dataset->Serialize(archive);

        archive.Close();
        archive_file.Close();
    } catch (std::exception& e) {
        cerr << "Error during save dataset: " << e.what() << endl;
    }
}

int main(int argc, char* argv[]) {
    const int kClassCount = 2;

    cxxopts::ParseResult args = ParseArgs(argc, argv);
    auto config_file = args["config"].as<string>();
    auto source_file = args["source"].as<string>();
    auto separator = args["sep"].as<string>();
    auto features_count = args["features-count"].as<int>();
    auto destination_file = args["destination"].as<string>();

    nlohmann::json config = ReadConfig(config_file);
    unique_ptr<CsvReader> reader = PrepareReader(source_file, separator);
    unique_ptr<PassengerInfoConverter> converter = PrepareConverter(config);
    unique_ptr<StandartScaler> scaler = PrepareStdScaler(config);

    int count = 0;
    vector<string> fields;

    CPtr<CMemoryProblem> dataset = new CMemoryProblem(features_count, kClassCount);

    while (reader->Next(fields)) {
        count++;
        PassengerInfo info;

        bool success = converter->FromStrings(fields, info);

        if (!success) {
            cout << "Bad line: " << count << endl;
            continue;
        }

        NeoML::CSparseFloatVector vect;
        int class_id = converter->Info2Vec(info, vect);
        vect = scaler->Transform(vect);

        dataset->Add(vect, class_id);
    }

    cout << "Vectors prepared: " << dataset->GetVectorCount() << endl;

    StoreDataset(dataset, destination_file);

    return 0;
}