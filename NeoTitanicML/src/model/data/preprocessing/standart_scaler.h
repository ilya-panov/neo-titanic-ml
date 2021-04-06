#ifndef NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_
#define NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_

#include <NeoML/NeoML.h>

#include "common.h"


namespace neotitanicml {

class StandartScaler {

public:

    /// Конструктор
    StandartScaler();

    /**
     * Задать значения мер
     * 
     * @param mean Вектор средних значений
     * @param std_deviation Вектор стандартных отклонений
     * @return Если размерности заданных векторов не совпадают вернётся false,
     *         иначе - true
     */
    bool SetMeasures(const std::vector<float>& mean,
                     const std::vector<float>& std_deviation);

    /**
     * Произвести трансформацию скалирования
     * 
     * @param vec вектор, который нужно скалировать
     * @return отскалированный вектор
     */
    const NeoML::CSparseFloatVector& Transform(
        NeoML::CSparseFloatVector& vec);

private:

    NeoML::CSparseFloatVector mean_;
    NeoML::CSparseFloatVector std_deviation_;

};

} // namespace neotitanicml


#endif  // NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_