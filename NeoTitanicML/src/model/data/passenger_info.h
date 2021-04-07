#ifndef NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_
#define NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_

#include "common.h"

namespace neotitanicml {

struct PassengerInfo {
    int surviveded;
    int pclass;
    std::string sex;
    int age;
    int sib_sp;
    int parch;
    float fare;
    std::string embarked;
};

}  // namespace neotitanicml

#endif  // NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_