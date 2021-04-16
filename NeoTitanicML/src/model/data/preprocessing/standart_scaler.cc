#include "standart_scaler.h"

#include <iostream>

using std::cerr;
using std::vector;

namespace neotitanicml {

StandartScaler::StandartScaler() {
    mean_.SetAt(0, 0.0);
    std_deviation_.SetAt(0, 1.0);
}

bool StandartScaler::SetMeasures(const vector<float>& mean,
                                 const vector<float>& std_deviation) {
    if (mean.size() != std_deviation.size()) {
        cerr << "Err: mean and std deviation have different size"
             << std::endl;
        return false;
    }

    mean_.Nullify();
    std_deviation_.Nullify();

    size_t size = mean.size();
    for (int i = 0; i < size; i++) {
        mean_.SetAt(i, mean[i]);
        std_deviation_.SetAt(i, std_deviation[i]);
    }

    return true;
}

const CSparseFloatVector& StandartScaler::Transform(CSparseFloatVector& vec) const {
    vec -= mean_;
    vec.DivideBy(std_deviation_);
    return vec;
}

}  // namespace neotitanicml
