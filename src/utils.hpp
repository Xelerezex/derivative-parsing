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

class Parser
{
public:
	explicit Parser(std::istream &streamToParse);

	// Деструктор
	~Parser() = default;

	// Удаленные конструкторы и операторы
	Parser() = delete;
	Parser(const Parser &) = delete;
	Parser(const Parser &&) = delete;
	Parser &operator=(const Parser &) = delete;
	Parser &operator=(const Parser &&) = delete;

private:
	std::istream &m_refStream;
};

/**
 * @brief Функция разделяет строку даваемую на вход, по какомуто разделителю
 *
 * @param input - входная строка
 * @param seperator - разделитель
 * @return стандартный вектор с разделенной строкой
 */
std::vector<std::string> split(const std::string &input, char seperator);

} // namespace utils

#endif