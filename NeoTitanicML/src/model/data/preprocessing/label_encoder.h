#ifndef NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_
#define NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_

#include <string>
#include <vector>
#include <map>


namespace neotitanicml {

/**
 * Кодирование строковых меток
 */
class LabelEncoder {

public:

    /**
     * Конструктор
     * 
     * @param labels Список меток
     */
    LabelEncoder(std::vector<std::string> labels);

    /**
     * Трансформировать метку в числовое представление
     * 
     * @param label Метка
     * @return Если метка известна, то вернётся целое число [0, ...].
     *         Если метка неизвестна, то вернётся -1.
     */
    int Transform(std::string label);

private:

    std::map<std::string, int> classes_;
};


} // namespace neotitanicml


#endif  // NEOTITANICML_MODEL_DATA_PREPROC_LABELENCODER_H_