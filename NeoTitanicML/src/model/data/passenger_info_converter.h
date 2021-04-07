#ifndef NEOTITANICML_MODEL_DATA_PASSENGERINFOCONVERTER_H_
#define NEOTITANICML_MODEL_DATA_PASSENGERINFOCONVERTER_H_

#include <NeoML/NeoML.h>

#include "common.h"
#include "model/data/preprocessing/label_encoder.h"
#include "passenger_info.h"

namespace neotitanicml {

class PassengerInfoConverter {
 public:
    PassengerInfoConverter() {}

    /**
     * Конструктор
     * 
     * @param expected_fields Ожидаемое коичество полей
     * @param min_age минимальный возраст - минимальная граница
     *                для случайного выбора
     * @param max_age максимальный возраст
     */
    PassengerInfoConverter(int expected_fields, int min_age, int max_age);

    /**
     * Задать кодировщики
     * 
     * @param sex_encoder Пол
     * @param embarked_encoder Подобранный
     */
    void SetEncoders(LabelEncoder sex_encoder, LabelEncoder embarked_encoder);

    /**
     * Конвертировать вектор строк в структуру информации
     * 
     * @param [in] strings вектор строк из исходных данных
     * @param [out] info структура с результатом конвертации
     * @return При успешной конвертации true
     */
    bool FromStrings(const std::vector<std::string>& strings,
                     PassengerInfo& info);

    /**
     * Проверить корректность данных в PassengerInfo
     * 
     * @param info Структура для проверки
     * @return Если данны корректны, то вернётся true
     */
    bool ValidateInfo(const PassengerInfo& info);

    /**
     * Перевести PassengerInfo в NeoML-вектор
     * 
     * @param [in] info Cтруктура с данными о пассажире
     * @param [out] vect Векто, полученный из данных
     * @return Идентификатор класса (в задаче классификации)
     * 
     * Необходимо, чтобы структура info сначала прошла валидацию!
     */
    int Info2Vec(const PassengerInfo& info, NeoML::CSparseFloatVector& vect);

 private:
    int expected_fields_;

    int min_age_;
    int max_age_;
    NeoML::CRandom random_;

    LabelEncoder sex_encoder_;
    LabelEncoder embarked_encoder_;

    bool Str2Int(const std::string& str, int& i);
    bool Str2Float(const std::string& str, float& f);
    bool ParseStrings(const std::vector<std::string>& strings,
                      PassengerInfo& info);
};

/*
class PassengerInfoConverterFactory {

public:

    PassengerInfoConverterFactory();

    PassengerInfoConverterFactory& FromJson(std::string json);

    PassengerInfoParser build();

};
*/

}  // namespace neotitanicml

#endif  // NEOTITANICML_MODEL_DATA_PASSENGERINFOCONVERTER_H_