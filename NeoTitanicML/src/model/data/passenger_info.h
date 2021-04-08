#ifndef NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_
#define NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_

#include "common.h"

namespace neotitanicml {

const int kMinAge = 0;
const int kMaxAge = 120;
const std::string kDefaultEmbarked = "S";

const std::string kJsonExpectedFields = "expected-fields";
const std::string kJsonMinAge = "min-age";
const std::string kJsonMaxAge = "max-age";
const std::string kJsonSexLabels = "sex-labels";
const std::string kJsonEmbarkedLabels = "embarked-labels";

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