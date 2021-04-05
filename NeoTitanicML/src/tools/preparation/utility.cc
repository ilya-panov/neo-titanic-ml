#include "tools/preparation/utility.h"

using std::string;
using std::vector;


namespace neotitanicml {


void split_string(const string& str,
                  const string& delimiter,
                  vector<string>& fields_out) {

    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != string::npos) {
        fields_out.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    fields_out.push_back(str.substr(prev));
}


}