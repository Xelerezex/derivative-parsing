#pragma once

#ifndef TOKEN_HPP
	#define TOKEN_HPP

	#include <istream>
	#include <memory>
	#include <vector>

	#include "tokentype.hpp"

/**
 * @brief Пространство имен для основного класса Токена и сопутствующих функций
 */
namespace token
{

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
	explicit Token(std::string value, const TokenType &type);

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
	 * @brief Деструктор
	 */
	~Token() = default;

	/**
	 * @brief Удаленный дефолтный конструктор
	 */
	Token() = delete;

	/**
	 * @brief Фабричная функция создает Токен, относительно переданной,
	 *        как аргумент строки
	 *
	 * @param value - строка, которую надо токенизировать
	 * @return Token - объект Token
	 */
	static Token createToken(const std::string &value);

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
	 * @param rhs - копируемый токен, чьи поля перейдут этому классу
	 */
	void copyAndSwap(Token rhs) noexcept;

private:
	/* Значение токена */
	std::string m_value;

	/* Тип токена */
	TokenType m_type;
};

/**
 * @brief Тип указателя на токен
 *
 */
using TokenPtr = std::shared_ptr<Token>;

} // namespace token

#endif