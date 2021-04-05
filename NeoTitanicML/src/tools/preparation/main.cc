#include <stdio.h>

#include "tools/preparation/csv_reader.h"

using namespace neotitanicml;


void f() {

    CsvReader reader("/home/ilya/iWorkspace/research/neoml/data/src/test.csv");

    if (reader.Init()) {
        printf("file opened\n");
    }

    std::vector<std::string> fields;
    while (reader.Next(fields)) {
        printf("%i\n", fields.size());
    }
}

int main() {
    printf("Data prep!\n");

    f();


    return 0;
}