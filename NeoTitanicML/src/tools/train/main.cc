#include <cxxopts.hpp>
#include <iostream>
#include <string>

#include "model/agent.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace neotitanicml;

void PrintHelp(const cxxopts::Options& options) {
    std::cout << options.help() << endl;
}

cxxopts::ParseResult ParseArgs(int argc, char* argv[]) {
    cxxopts::Options options("train", "Train the model");

    options.add_options()
        ("h,help", "Print usage")
        ("m,model", "Path to save model", cxxopts::value<string>())
        ("t,train", "Train dataset", cxxopts::value<string>())
        ("y,test", "Train dataset", cxxopts::value<string>())
    ;

    try {
        auto args = options.parse(argc, argv);

        if (args.count("help")) {
            PrintHelp(options);
            std::exit(0);
        }

        if ((!args.count("model")) ||
            (!args.count("train")) ||
            (!args.count("test"))) {
            cerr << "ERROR: not define some arguments!"
                 << endl
                 << endl;
            PrintHelp(options);
            std::exit(1);
        }

        return args;

    } catch (std::exception& e) {
        cerr << "ERROR: " << e.what() << endl
             << endl;
        PrintHelp(options);
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    cxxopts::ParseResult args = ParseArgs(argc, argv);
    auto model_path = args["model"].as<string>();
    auto train_path = args["train"].as<string>();
    auto test_path = args["test"].as<string>();

    Agent agent(model_path, train_path, test_path);
    if (!agent.Init()) {
        cerr << "Error with train"
             << endl;
        return 1;
    }

    agent.Train();
    agent.SaveModel();

    return 0;
}