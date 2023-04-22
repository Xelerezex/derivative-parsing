#pragma once

#ifndef TOKENTYPE_HPP
	#define TOKENTYPE_HPP

	#include <cstdint>

/**
 * @brief Пространство имен для основного класса Токена и сопутствующих функций
 */
namespace token
{

// TODO: Что если встреченное число будет отрицательным. Нужен новый тип
//       или алгоритм shunting yard справляется с такимим вещами? Проверить.
/**
 * @brief Перечислитель с типом токена.
 */
enum class Type : int8_t
{
	/* Отсутствие типа у токена */
	None = 0,

	/** Число. */
	Number,

	/** Математическая переменная. */
	Variable,

	/** Левая круглая скобка. */
	LeftParenthesis,

	/** Правая круглая скобка. */
	RightParenthesis,

	/** Знак сложения. */
	Plus,

	/** Знак вычитания. */
	Minus,

	/** Знак умножения. */
	Multiplication,

	/** Знак деления. */
	Division,

	/** Знак возведения в степень. */
	Exponentiation,
};

/**
 * @brief Перечислитель со свойством ассоциативности токена.
 */
enum class Association : int8_t
{
	/** Отсутствие ассоциативности. */
	None = 0,

	/** Левая ассоциативность. */
	Left,

	/** Правая ассоциативности. */
	Right
};

/**
 * @brief Структура, представляющая собой тип токена
 */
struct TokenType
{
	/* Тип токена */
	Type type;

	/* Старшинство токена */
	unsigned int precedence;

	/* Ассоциативность токена */
	Association association;

	/**
	 * @brief Оператор проверки равенства двух типов токенов
	 *
	 * @param rhs - Тип токена справа от ==
	 * @param lhs - Тип токена слева от ==
	 * @return true - Типы токена равны
	 * @return false - Типы токена не равны
	 */
	friend bool operator==(const TokenType &rhs, const TokenType &lhs);

	/**
	 * @brief Функция обменивает местами значения двух TokenType
	 *
	 * @param lhs - первый тип токена на обмен
	 * @param rhs - второй тип токена на обмен
	 */
	friend void swap(TokenType &lhs, TokenType &rhs);
};

} // namespace token

#endif