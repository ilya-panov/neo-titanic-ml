#ifndef NEOTITANICML_TOOLS_PREP_UTILITY_H_
#define NEOTITANICML_TOOLS_PREP_UTILITY_H_

#include "common.h"

namespace neotitanicml {

/**
 * Разбиение строки с помощью разделителя
 * 
 * @param [in] str исходная строка
 * @param [in] delimiter разделитель
 * @return полученный вектор строк
 */
std::vector<std::string> SplitString(const std::string& str,
                                     const std::string& delimiter);

}  // namespace neotitanicml

#endif  // NEOTITANICML_TOOLS_PREP_UTILITY_H_