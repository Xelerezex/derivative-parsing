#pragma once

#ifndef UTILS_H
	#define UTILS_H
	#include <string>
	#include <vector>
	#include <cassert>

	/**
	 * @brief Макрос позволяет вызывать assert с сообщением
	 *
	 * @param exp - проверяемое выражение
	 * 				(true или false на вход. Срабатывает если передан false)
	 * @param msg - сообщение при ошибке
	 */
	#define assertm(exp, msg) assert(((void)msg, exp))

/**
 * @brief Пространство имен с функциями общего назначения
 */
namespace utils
{

/**
 * @brief Функция разделяет строку даваемую на вход, по какомуто разделителю
 *
 * @param input - строка на вход
 * @param seperator - разделитель
 * @return стандартный вектор с разделенной строкой
 */
std::vector<std::string> split(const std::string &input, char seperator);

/**
 * @brief Функция опрделяет, считается ли данная на вход строка числом
 *
 * @param inputStr - строка на вход
 * @return true - считается числом
 * @return false - не считается числом
 */
bool isNumber(const std::string &inputStr);

/**
 * @brief Функция опрделяет, считается ли данная на вход строка переменной.
 *        Переменной считается только одна буква от A до Z и от a до z (A != a).
 *
 * @param inputStr - строка на вход
 * @return true - считается переменной
 * @return false - не считается переменной
 */
bool isVariable(const std::string &inputStr);

/**
 * @brief Функция опрделяет, считается ли данная на вход строка левой круглой
 * 		  скобкой.
 *
 * @param inputStr - строка на вход
 * @return true - считается левой круглой скобкой
 * @return false - не считается левой круглой скобкой
 */
bool isLeftParenthesis(const std::string &inputStr);

/**
 * @brief Функция опрделяет, считается ли данная на вход строка правой круглой
 * 		  скобкой.
 *
 * @param inputStr - строка на вход
 * @return true - считается правой круглой скобкой
 * @return false - не считается правой круглой скобкой
 */
bool isRightParenthesis(const std::string &inputStr);

} // namespace utils

#endif