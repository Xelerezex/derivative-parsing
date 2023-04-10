#pragma once

#ifndef TOKEN_HPP
#	define TOKEN_HPP

#	include <cstdint>
#	include <istream>
#	include <memory>
#	include <vector>

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
	/** Число. */
	Number = 0,

	/** Математическая переменная. */
	Variable,

	/** Левая круглая скобка. */
	LeftParenthesis,

	/** Правая круглая скобка. */
	RightParenthesis
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
 * @brief Перечислитель с ошибками, встречающимися при работе
 *        с токенами
 */
enum class Error : int16_t
{
	/** Отсутсвие ошибки. Корректная отработка */
	None = 0,

	/** Некая обычная ошибка */
	DefaultError = -1,

	/** При парсинге возник неизвестный символ */
	UnknownToken = -2,

	/** На парсинг была дана пустая строка */
	EmptyString = -3,

	/** Ошибка парсинга единицы (unit) слова из стрима */
	WordParsingError = -4,
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
};

/**
 * @brief Структура, представляющая собой целый токен.
 *        Любое значение токена конвертируется в строку.
 */
struct Token
{
	/* Значение токена */
	std::string value;

	/* Тип токена */
	TokenType type;
};

/**
 * @brief Тип указателя на токен
 *
 */
using TokenPtr = std::shared_ptr<Token>;

/**
 * @brief Оператор проверки равенства двух типов токенов
 *
 * @param rhs - Тип токена справа от ==
 * @param lhs - Тип токена слева от ==
 * @return true - Типы токена равны
 * @return false - Типы токена не равны
 */
bool operator==(const TokenType &rhs, const TokenType &lhs);

/**
 * @brief Оператор проверки равенства двух токенов
 *
 * @param rhs - Токен справа от ==
 * @param lhs - Токен слева от ==
 * @return true - Токены равны
 * @return false - Токены не равны
 */
bool operator==(const Token &rhs, const Token &lhs);

} // namespace token

#endif