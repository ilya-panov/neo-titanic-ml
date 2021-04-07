#include "passenger_info_converter.h"

#include <iostream>

using std::cerr;
using std::string;
using std::vector;
using namespace NeoML;

namespace neotitanicml {

PassengerInfoConverter::PassengerInfoConverter(
    int expected_fields, int min_age, int max_age) : expected_fields_(expected_fields),
                                                     min_age_(min_age),
                                                     max_age_(max_age_) {
    random_ = NeoML::CRandom();
}

void PassengerInfoConverter::SetEncoders(LabelEncoder sex_encoder,
                                         LabelEncoder embarked_encoder) {
    sex_encoder_ = sex_encoder;
    embarked_encoder_ = embarked_encoder;
}

bool PassengerInfoConverter::FromStrings(const vector<string>& strings,
                                         PassengerInfo& info) {
    bool success = ParseStrings(strings, info);
    if (!success) {
        return false;
    }

    return ValidateInfo(info);
}

bool PassengerInfoConverter::ParseStrings(const vector<string>& strings,
                                          PassengerInfo& info) {
    if (strings.size() != expected_fields_) {
        cerr << "WARN: bad fields count: expected='" << expected_fields_
             << "' exist='" << strings.size() << "'"
             << "\n";
        return false;
    }

    if (!Str2Int(strings[1], info.surviveded)) {
        cerr << "Err with surviveded"
             << "\n";
        return false;
    }

    if (!Str2Int(strings[2], info.pclass)) {
        cerr << "Err with pclass"
             << "\n";
        return false;
    }

    if (strings[3].length()) {
        info.sex = strings[3];
    } else {
        cerr << "Err with sex"
             << "\n";
        return false;
    }

    if (!Str2Int(strings[4], info.age)) {
        info.age = random_.UniformInt(min_age_, max_age_);
    }

    if (!Str2Int(strings[5], info.sib_sp)) {
        cerr << "Err with sib_sp"
             << "\n";
        return false;
    }

    if (!Str2Int(strings[6], info.parch)) {
        cerr << "Err with sib_sp"
             << "\n";
        return false;
    }

    if (!Str2Float(strings[7], info.fare)) {
        cerr << "Err with fare"
             << "\n";
        return false;
    }

    if (strings[8].length()) {
        info.embarked = strings[8];
    } else {
        info.embarked = "S";
    }

    return true;
}

bool PassengerInfoConverter::ValidateInfo(const PassengerInfo& info) {
    string not_exist = " does not exist";

    if (!sex_encoder_.Exist(info.sex)) {
        cerr << "Err sex " << info.sex << not_exist << "\n";
        return false;
    }
    if (!embarked_encoder_.Exist(info.embarked)) {
        cerr << "Err embarked " << info.embarked << not_exist << "\n";
        return false;
    }
    if ((info.age < 0) || (info.age > 120)) {
        cerr << "Err age " << info.age << not_exist << "\n";
        return false;
    }

    return true;
}

int PassengerInfoConverter::Info2Vec(const PassengerInfo& info,
                                     CSparseFloatVector& vect) {
    vector<float> floats = {
        static_cast<float>(info.pclass),
        static_cast<float>(sex_encoder_.Transform(info.sex)),
        static_cast<float>(info.age),
        static_cast<float>(info.sib_sp),
        static_cast<float>(info.parch),
        info.fare,
        static_cast<float>(embarked_encoder_.Transform(info.embarked))};

    int i = 0;
    for (float f : floats) {
        vect.SetAt(i, f);
        i++;
    }

    return info.surviveded;
}

bool PassengerInfoConverter::Str2Int(const string& str, int& i) {
    try {
        i = std::stoi(str, nullptr);
        return true;
    } catch (std::invalid_argument e) {
        //cerr << "Err: " << e.what() << "\n";
        return false;
    }
}

bool PassengerInfoConverter::Str2Float(const string& str, float& f) {
    try {
        f = std::stof(str, nullptr);
        return true;
    } catch (std::invalid_argument e) {
        //cerr << "Err: " << e.what() << "\n";
        return false;
    }
}

}  // namespace neotitanicml