#include "standart_scaler.h"

#include <iostream>

using std::vector;
using std::cout;

namespace neotitanicml {
    
    StandartScaler::StandartScaler() {
        mean_.SetAt(0, 0.0);
        std_deviation_.SetAt(0, 0.0);
    }

    bool StandartScaler::SetMeasures(const vector<float>& mean,
                                     const vector<float>& std_deviation) {
        
        if (mean.size() != std_deviation.size()) {
            cout << "Err: mean and std deviation have different size"
                << "\n";
            return false;
        }

        mean_.Nullify();
        std_deviation_.Nullify();

        int size = mean.size();
        for (int i = 0; i < size; i++) {
            mean_.SetAt(i, mean[i]);
            std_deviation_.SetAt(i, std_deviation[i]);
        }

        return true;
    }


    const CSparseFloatVector& StandartScaler::Transform(CSparseFloatVector& vec) {
        vec -= mean_;
        vec.DivideBy(std_deviation_);
        return vec;
    }




} // namespace neotitanicml
