#include "csv_reader.h"

#include <sstream>

#include "tools/preparation/utility.h"

using std::string;
using std::vector;

namespace neotitanicml {

bool CsvReader::Init() {
    infile_ = std::ifstream(file_path_);
    if (!infile_.is_open()) {
        return false;
    }
    return true;
}

CsvReader::~CsvReader() {
    infile_.close();
}

bool CsvReader::Next(vector<string>& fields_out) {
    fields_out.clear();

    if (!std::getline(infile_, line_)) {
        return false;
    }

    fields_out = SplitString(line_, sep_);
    return true;
}

}  // namespace neotitanicml