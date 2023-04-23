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

token::TokenList::TokenList(const TokenList &&rhs) noexcept
	: m_tokens{std::move(rhs.m_tokens)}
{
}

token::TokenList &token::TokenList::operator=(const TokenList &rhs) noexcept
{
	copyAndSwap(rhs);
	return *this;
}

token::TokenList &token::TokenList::operator=(const TokenList &&rhs) noexcept
{
	copyAndSwap(std::move(rhs));
	return *this;
}

token::TokenList::Error token::TokenList::tokenizer(const std::string &inputStr,
													TokensList &outputTokens)

token::TokenList::Error token::TokenList::tokenize(const std::string &inputStr,
												   TokensList &outputTokens)
{
	Error errorCode{Error::None};

	if (inputStr.empty())
	{
		errorCode = Error::EmptyString;
	}

	// Вывод результа парсинга из функции
	outputTokens = m_tokens;

	return errorCode;
}

void token::TokenList::copyAndSwap(TokenList rhs) noexcept
{
	m_tokens.swap(rhs.m_tokens);
}
