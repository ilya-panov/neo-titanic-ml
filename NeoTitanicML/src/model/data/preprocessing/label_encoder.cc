#include "label_encoder.h"

using std::string;
using std::vector;

namespace neotitanicml {

LabelEncoder::LabelEncoder(const vector<string>& labels) {
    int class_id = 0;
    for (auto label : labels) {
        classes_[label] = class_id;
        class_id++;
    }
}

int LabelEncoder::Transform(const string& label) const {
    if (classes_.count(label)) {
        return classes_.at(label);
    }

    return -1;
}

bool LabelEncoder::Exist(const std::string& label) const {
    if (classes_.count(label)) {
        return true;
    }
    return false;
}

}  // namespace neotitanicml