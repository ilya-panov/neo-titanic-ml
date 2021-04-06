#ifndef NEOTITANICML_TOOLS_PREP_UTILITY_H_
#define NEOTITANICML_TOOLS_PREP_UTILITY_H_

#include "common.h"


namespace neotitanicml {

/**
 * Разбиение строки с помощью разделителя
 * 
 * @param [in] str исходная строка
 * @param [in] delimiter разделитель
 * @param [out] fields_out полученный вектор строк
 */
void SplitString(const std::string& str,
                 const std::string& delimiter,
                 std::vector<std::string>& fields_out);


} // namespace neotitanicml

#endif  // NEOTITANICML_TOOLS_PREP_UTILITY_H_