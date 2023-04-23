#pragma once

#ifndef TOKENLIST_HPP
	#define TOKENLIST_HPP

	#include "token.hpp"

namespace token
{

/** Тип считающийся типом основного контейнера данного класса */
using TokensList = std::vector<token::Token>;

class TokenList
{
public:
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

		/** Ошибка при возвращении слова обратно в стрим*/
		ParsingUngetError = -5,
	};

public:
	/**
	 * @brief Дефолтный конструктор
	 */
	TokenList() = default;

	/**
	 * @brief Конструктор, принимающий на вход вектор с Токенами
	 *
	 * @param tokens  - вектор с Токенами, которые копируется, потом копия
	 * 				    мувается
	 */
	explicit TokenList(TokensList tokens);

	/**
	 * @brief Конструктор копирования
	 *
	 * @param rhs  - список с токенами, которые копируется
	 */
	TokenList(const TokenList &rhs) noexcept;

	/**
	 * @brief Констуктор перемещения
	 *
	 * @param rhs  - rvalue значение списока с токенами
	 */
	TokenList(TokenList &&rhs) noexcept;

	/**
	 * @brief Оператор присваивания копии
	 *
	 * @param rhs - список с токенами, которые копируются
	 * @return TokenList& - ссылка на этот объект
	 */
	TokenList &operator=(const TokenList &rhs) noexcept;

	/**
	 * @brief Move-оператор присваивания
	 *
	 * @param rhs - rvalue значение списока с токенами
	 * @return TokenList& - ссылка на этот объект
	 */
	TokenList const &operator=(TokenList &&rhs) noexcept;

	/**
	 * @brief Деструктор
	 */
	~TokenList() = default;

	/**
	 * @brief Возвращает размер внутреннего контейнера, соответсвует
	 *        количеству хранящихся токенов
	 *
	 * @return количество токенов в контейнере
	 */
	[[nodiscard]] size_t size() const noexcept;

	/**
	 * @brief Метод парсит строку, полученную на вход, и превращает её
	 *        вектор, со связками Значение-Токен (класс Token).
	 *
	 * @param inputStr строка, идущая на вход
	 * @return код ошибки. Error::None - если функция отработала успешно
	 */
	Error tokenize(const std::string &inputStr);

	/**
	 * @brief Оператор проверки равенства двух листов с токенами
	 *
	 * @param rhs - лист с токенами справа от ==
	 * @param lhs - лист с токенами слева от ==
	 * @return true - листы с токенами равны
	 * @return false - листы с токенами не равны
	 */
	friend bool operator==(const TokenList &rhs, const TokenList &lhs);

private:
	/**
	 * @brief Функция копирует объект, и потом подменяет его поля с полями этого
	 *        класса (Copy-n-Swap идиома).
	 *
	 * @param rhs - копируемый список с токенами
	 */
	void copyAndSwap(TokenList rhs) noexcept;

private:
	/** Вектор со всеми Токенами */
	TokensList m_tokens;
};

} // namespace token

#endif