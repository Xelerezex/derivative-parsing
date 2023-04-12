#pragma once

#ifndef UTILS_H
#	define UTILS_H
#	include <string>
#	include <vector>

/**
 * @brief Пространство имен с функциями общего назначения
 */
namespace utils
{

/**
 * @brief Функция разделяет строку даваемую на вход, по какомуто разделителю
 *
 * @param input - входная строка
 * @param seperator - разделитель
 * @return стандартный вектор с разделенной строкой
 */
std::vector<std::string> split(const std::string &input, char seperator);

bool isNumber(const std::string &inputStr);

} // namespace utils

#endif