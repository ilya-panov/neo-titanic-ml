#include <iostream>
#include <string>

//#include <boost/program_options.hpp>
#include <NeoML/NeoML.h>

#include <cxxopts.hpp>

#include "model/agent.h"

using std::cerr;
using std::cout;
using std::string;
using std::vector;
using namespace neotitanicml;

void PrintHelp(const cxxopts::Options& options) {
    std::cout << options.help() << "\n";
}

cxxopts::ParseResult ParseArgs(int argc, char* argv[]) {
    cxxopts::Options options("test", "Test the model");

    options.add_options()
        ("h,help", "Print usage")
        ("m,model", "Path to load model", cxxopts::value<string>())
        ("y,test", "Train dataset", cxxopts::value<string>())
    ;

    try {
        auto args = options.parse(argc, argv);

        if (args.count("help")) {
            PrintHelp(options);
            std::exit(0);
        }

        if ((!args.count("model")) ||
            (!args.count("test"))) {
            cerr << "ERROR: not define some arguments!"
                 << "\n\n";
            PrintHelp(options);
            std::exit(1);
        }

        return args;

    } catch (std::exception& e) {
        cerr << "ERROR: " << e.what() << "\n\n";
        PrintHelp(options);
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    cxxopts::ParseResult args = ParseArgs(argc, argv);
    auto model_path = args["model"].as<string>();
    auto test_path = args["test"].as<string>();

    Agent agent(model_path, test_path);
    agent.Init();
    agent.LoadModel();

    float accuracy = agent.Validate();

    cout << "ACCURACY: " << accuracy * 100 << "\n";

    return 0;
}