#pragma once

#ifndef TOKENLIST_HPP
	#define TOKENLIST_HPP

	#include "token.hpp"

namespace token
{

// TODO [0]: Создать всю перефирию для класса TokenList, создать в нем метод
// tokenize, который будет заниматься токенизацией целой строки.
// Все протестировать

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
	};

public:
	/**
	 * @brief Дефолтный конструктор
	 *
	 */
	TokenList() = default;

	/**
	 * @brief Метод парсит строку, полученную на вход, и превращает её
	 *        вектор, со связками Значение-Токен (класс Token).
	 *
	 * @param inputStr строка, идущая на вход
	 * @param outputTokens вектор с токенами, который получится после парсинга
	 * @return код ошибки. Error::None - если функция отработала успешно
	 */
	Error tokenizer(const std::string &inputStr, TokensList &outputTokens);

	/**
	 * @brief Деструктор
	 */
	~TokenList() = default;

private:
	/** Вектор со всеми Токенами */
	TokensList m_tokens;
};

} // namespace token

#endif