#include "tokenlist.hpp"

#include "utils.hpp"
#include <sstream>

#ifdef WHEN_DEBUG_MODE
	#include <thread>
	#include <iostream>
#endif

/* -------------------------------------------------------------------------- */
bool token::operator==(const TokenList &rhs, const TokenList &lhs)
{
	return rhs.size() == lhs.size() && rhs.m_tokens == lhs.m_tokens;
}

/* -------------------------------------------------------------------------- */
token::TokenList::TokenList(TokensList tokens)
	: m_tokens{std::move(tokens)}
{
}

token::TokenList::TokenList(const TokenList &rhs) noexcept
	: m_tokens{rhs.m_tokens}
{
}

token::TokenList::TokenList(TokenList &&rhs) noexcept
	: m_tokens{std::move(rhs.m_tokens)}
{
}

token::TokenList &token::TokenList::operator=(const TokenList &rhs) noexcept
{
	copyAndSwap(rhs);
	return *this;
}

token::TokenList const &token::TokenList::operator=(TokenList &&rhs) noexcept
{
	copyAndSwap(std::move(rhs));
	return *this;
}

size_t token::TokenList::size() const noexcept
{
	return m_tokens.size();
}

/**
 * @brief Шаблонная функция, используемая только в этой единице трансляции.
 *        Нужна для парсинга целого "слова" из стрима
 *
 * @tparam Type - шаблонный тип
 * @param  stream - стрим, из которого будет считываться слово
 * @param  output - спаршенное строковое значение
 * @return код ошибки. Error::None - в случае успеха
 */
template<typename Type>
token::TokenList::Error parseUnit (std::istream &stream, std::string &output)
{
	using Error = token::TokenList::Error;

	Type word;
	if (!(stream >> word))
	{
		return Error::WordParsingError;
	}

	// Если тип является строкой, его не надо приводить к строке
	if constexpr (std::is_same_v<int, Type>)
	{
		output = std::to_string(word);
	}
	else
	{
		output = std::string{word};
	}

#ifdef WHEN_DEBUG_MODE
	std::cout << "Unit = " << output << std::endl;
#endif

	return Error::None;
}

/**
 * @brief Шаблонная функция, используемая только в этой единице трансляции.
 *        Нужна для возврата, последнего спаршенного слова обратно в стрим
 *
 * @param  stream - стрим, из которого слово было спаршено, и куда вернется
 * @return код ошибки. Error::None - в случае успеха
 */
token::TokenList::Error returnCharToStream (std::istream &stream)
{
	using Error = token::TokenList::Error;

	if (!(stream.unget()))
	{
		return Error::ParsingUngetError;
	}

	return Error::None;
}

/**
 * @brief Функция, используемая только в этой единице трансляции.
 *        Нужна для парсинга целого "слова" и создания из него токена
 *
 * @tparam Type - шаблонный тип
 * @param  stream - стрим, из которого будет считываться слово
 * @param  token - токен, получаемый после парсинга
 * @return код ошибки. Error::None - в случае успеха
 */
token::TokenList::Error parseUnitToToken (std::istream &stream,
										  token::Token &token)
{
	using Error = token::TokenList::Error;
	Error errorCode{Error::None};
	std::string unit;

	char character = static_cast<char>(stream.peek());

	// Если попался пробел, просто выкидываем его
	const bool isSpace = static_cast<bool>(std::isspace(character));
	if (isSpace)
	{
		stream.get();
		return errorCode;
	}

	const bool isDigit = static_cast<bool>(std::isdigit(character));
	const bool isAlpha = static_cast<bool>(std::isalpha(character));
	const bool isSymbol = character == '+' || character == '*'
						  || character == '^' || character == '('
						  || character == ')' || character == '/';
	const bool isMinus = character == '-';
	if (isDigit)
	{
		errorCode = parseUnit<int>(stream, unit);
	}
	else if (isAlpha || isSymbol)
	{
		errorCode = parseUnit<char>(stream, unit);
	}
	else if (isMinus)
	{
		character = stream.get();
		if (static_cast<bool>(std::isdigit(stream.peek())))
		{
			errorCode = returnCharToStream(stream);
			errorCode = parseUnit<int>(stream, unit);
		}
		else
		{
			errorCode = returnCharToStream(stream);
			errorCode = parseUnit<char>(stream, unit);
		}
	}
	else
	{
		errorCode = Error::UnknownToken;
	}

	// Сохраняем полученный, после парсинга токен только, если нет ошибок
	if (errorCode == Error::None)
	{
		token = token::Token::createToken(unit);
	}

	return errorCode;
}

token::TokenList::Error token::TokenList::tokenize(const std::string &inputStr)
{
	TokensList temporary;
	Error errorCode{Error::None};

	if (inputStr.empty())
	{
		errorCode = Error::EmptyString;
	}

	std::stringstream stream{inputStr};

	while (stream.peek() != std::char_traits<char>::eof())
	{
		Token token;
		errorCode = parseUnitToToken(stream, token);
		if (errorCode != Error::None)
		{
			break;
		}

		// Не записываем token, если он с дефолтными значениями
		if (!token.isNone())
		{
			temporary.push_back(token);
		}
	}

	// Сохранение резултата при отсутствии ошибок
	if (errorCode == Error::None)
	{
		m_tokens = std::move(temporary);
	}

	return errorCode;
}

void token::TokenList::copyAndSwap(TokenList rhs) noexcept
{
	m_tokens.swap(rhs.m_tokens);
}
