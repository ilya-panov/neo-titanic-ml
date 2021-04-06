#include <stdio.h>

#include <iostream>
#include <fstream>
#include <sstream>

//#include <boost/program_options.hpp>
#include <cxxopts.hpp>
#include <nlohmann/json.hpp>
#include <NeoML/NeoML.h>


using std::string;
using std::vector;
using std::cout;
using std::cerr;


vector<string> split_string(const string& str,
                            const string& delimiter)
{
    vector<string> strings;

    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}


cxxopts::ParseResult parse(int argc, char* argv[]) {

    cxxopts::Options options("test", "A brief description");

    options.add_options()
        ("b,bar", "Param bar", cxxopts::value<string>())
        ("d,debug", "Enable debugging", cxxopts::value<bool>()->default_value("false"))
        ("f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))
        ("h,help", "Print usage")
    ;

    try{
        auto result = options.parse(argc, argv);
    

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            //return result;
            std::exit(0);
        }

        return result;
    }catch (std::exception& e) {
        cerr << e.what() << "\n";
        std::exit(1);
    }
}

int main(int argc, char* argv[]) {
    printf("Train!\n");


    auto result = parse(argc, argv);

    cout << result["foo"].as<int>() << "\n";






    //IMathEngine& math_engine = GetDefaultCpuMathEngine();
    //CRandom random(451);


    CSparseFloatVector vec(10);

    for (int i=0; i<10; i++) {
        vec.SetAt(i, i + 5);
    }

    vec.SquareEachElement();

    printf("res = %f %f\n", vec.GetValue(0), vec.GetValue(1));


    string s("");

    try {
        printf("%i\n", std::stoi(s, nullptr));
    } catch (std::invalid_argument) {
        printf("Ошибка с %s\n", s.c_str());
    }
    

    //NeoML::CMemoryProblem *dataset = new NeoML::CMemoryProblem(10, 2);
    //dataset->Add(vec, 0);

    
    vector<string> strings = split_string(s, "|");

    std::cout << strings.size() << "\n" << std::ends;

    CPtr<CMemoryProblem> dataset = new CMemoryProblem(10, 2);

    //NeoML::CMemoryProblem dataset(10, 2);


    std::ifstream* infile;
    infile = new std::ifstream("/home/ilya/iWorkspace/research/neoml/data/src/test.csv2");
    string line;
    while (std::getline(*infile, line)) {
        printf("%s\n", line.c_str());
    }
    infile->close();
    delete infile;


    //CpuMathEngineCleanUp();
    return 0;
}