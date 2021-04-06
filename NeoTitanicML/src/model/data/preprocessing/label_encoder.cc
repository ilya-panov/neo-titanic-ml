#include "label_encoder.h"


using std::vector;
using std::string;


namespace neotitanicml {

    LabelEncoder::LabelEncoder(vector<string> labels) {
        int class_id = 0;
        for (auto label : labels) {
            classes_[label] = class_id;
            class_id++;
        }
    }


    int LabelEncoder::Transform(string label) {
        if (classes_.count(label)) {
            return classes_.at(label);
        }

        return -1;
    }




}