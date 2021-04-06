#include "csv_reader.h"

#include <fstream>
#include <sstream>

#include "tools/preparation/utility.h"

using std::string;
using std::vector;


namespace neotitanicml {


bool CsvReader::Init() {
    infile_ = new std::ifstream(file_path_);
    if (!infile_->is_open()) {
        return false;
    }
    return true;
}

CsvReader::~CsvReader() {
    if (infile_ != nullptr) {
        infile_->close();
        delete infile_;
    }
}


bool CsvReader::Next(vector<string>& fields_out) {
    fields_out.clear();

    if (!std::getline(*infile_, line_)) {
        return false;
    }

    SplitString(line_, sep_, fields_out);
    return true;
}

} // namespace neotitanicml