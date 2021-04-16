#ifndef NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_
#define NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_

#include "common.h"

namespace neotitanicml {

static const int kMinAge = 0;
static const int kMaxAge = 120;
static const std::string kDefaultEmbarked = "S";

static const std::string kJsonExpectedFields = "expected-fields";
static const std::string kJsonMinAge = "min-age";
static const std::string kJsonMaxAge = "max-age";
static const std::string kJsonSexLabels = "sex-labels";
static const std::string kJsonEmbarkedLabels = "embarked-labels";

struct PassengerInfo {
    std::string sex;
    std::string embarked;
    int surviveded;
    int pclass;
    int age;
    int sib_sp;
    int parch;
    float fare;
};

}  // namespace neotitanicml

#endif  // NEOTITANICML_MODEL_DATA_PASSENGERINFO_H_