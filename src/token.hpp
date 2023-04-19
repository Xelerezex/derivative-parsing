#pragma once

#ifndef TOKEN_HPP
	#define TOKEN_HPP

	#include <cstdint>
	#include <istream>
	#include <memory>
	#include <vector>

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

/**
 * @brief Класс, представляющая собой целый токен.
 *        Любое значение токена конвертируется в строку.
 */
class Token
{
public:
	/**
	 * @brief Основной конструктор
	 *
	 * @param value - значение токена
	 * @param type  - тип токена
	 */
	explicit Token(const std::string &value, const TokenType &type);

	/**
	 * @brief Оператор присваивания копии.
	 *
	 * @param rhs - токен, который копируется
	 * @return Token& - ссылка на этот объект
	 */
	Token &operator=(const Token &rhs) noexcept;

	/**
	 * @brief Move-оператор присваивания
	 *
	 * @param rhs - rvalue токен
	 * @return Token& - ссылка на этот объект
	 */
	Token &operator=(const Token &&rhs) noexcept;

	/**
	 * @brief Конструктор копирования
	 *
	 * @param rhs  - токен, который копируется
	 */
	Token(const Token &rhs) noexcept;

	/**
	 * @brief Констуктор перемещения
	 *
	 * @param rhs  - rvalue токен
	 */
	Token(const Token &&rhs) noexcept;

	static Token createToken(const std::string &value);

	/**
	 * @brief Деструктор
	 */
	~Token() = default;

	/**
	 * @brief Удаленный дефолтный конструктор
	 */
	Token() = delete;

	/**
	 * @brief Оператор проверки равенства двух токенов
	 *
	 * @param rhs - Токен справа от ==
	 * @param lhs - Токен слева от ==
	 * @return true - Токены равны
	 * @return false - Токены не равны
	 */
	friend bool operator==(const Token &rhs, const Token &lhs);

	/**
	 * @brief Функция обменивает местами значения двух Токенов
	 *
	 * @param lhs - первый токен на обмен
	 * @param rhs - второй токен на обмен
	 */
	friend void swap(Token &lhs, Token &rhs);

private:
	/**
	 * @brief Функция копирует объект, и потом подменяет его поля с полями этого
	 *        класса (Copy-n-Swap идиома).
	 *
	 * @param rhs - токен, чьи поля передут этому классу.
	 */
	void copyAndSwap(const Token &rhs) noexcept;

private:
	/* Значение токена */
	std::string m_value;

	/* Тип токена */
	TokenType m_type;
};

// TODO [2]: Разбить проект на три файла TokenType Token TokenList -> и так же
// сделать для тестов, а то становится неудобно

// TODO [3]: Создать класс TokenList и создать в нем метод tokenize, который
// будет заниматься токенизацией целой строки

/**
 * @brief Тип указателя на токен
 *
 */
using TokenPtr = std::shared_ptr<Token>;

} // namespace token

#endif