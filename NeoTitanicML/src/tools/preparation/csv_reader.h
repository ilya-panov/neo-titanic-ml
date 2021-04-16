#ifndef NEOTITANICML_TOOLS_PREP_CSVREADER_H_
#define NEOTITANICML_TOOLS_PREP_CSVREADER_H_

#include <fstream>
#include <iostream>

#include "common.h"

namespace neotitanicml {

/**
 * Чтение csv-файла и разбиение строк согласно разделителю
 */
class CsvReader final {
 public:
    /**
     * Конструктор
     * 
     * @param file_path путь к csv-файлу
     * @param sep разделитель полей в файле (по-умолчанию: ';')
     */
    CsvReader(const std::string& file_path, const std::string& sep = ";") : file_path_(file_path), sep_(sep) {}

    /// Деструктор
    ~CsvReader();

    /**
     * Проинициализировать парсер.
     * 
     * @return Если успех, то true.
     */
    bool Init();

    /**
     * Прочитать из файла и распарсить следующую строку
     * 
     * @param[out] fields_out вектор строк, полученный от разбиения разделителем
     *                        прочитанной строки
     * @return Если удалось прочитать строку - true.
     * 
     * Метод перед работой всегда очищает вектор fields_out.
     */
    bool Next(std::vector<std::string>& fields_out);

 private:
    std::string file_path_;
    std::ifstream infile_;
    std::string line_;
    std::string sep_;
};

}  // namespace neotitanicml

#endif  // NEOTITANICML_TOOLS_PREP_CSVREADER_H_