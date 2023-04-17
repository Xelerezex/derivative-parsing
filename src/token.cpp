#include "token.hpp"

#include "utils.hpp"

#include <cassert>
#include <config-file.hpp>

#ifdef WHEN_DEBUG_MODE
#	define DEBUG_UNUSED(x) (void) (x);
#	include <chrono>
#	include <iostream>
#	include <thread>
#endif

/* ------------------------- Относится к TokenType -------------------------- */
void token::swap(token::TokenType &lhs, token::TokenType &rhs)
{
	std::swap(rhs.type, lhs.type);
	std::swap(rhs.precedence, lhs.precedence);
	std::swap(rhs.association, lhs.association);
}

bool token::operator==(const token::TokenType &rhs, const token::TokenType &lhs)
{
	return static_cast<int8_t>(rhs.type) == static_cast<int8_t>(lhs.type)
		&& static_cast<unsigned int>(rhs.precedence)
			   == static_cast<unsigned int>(lhs.precedence)
		&& static_cast<int8_t>(rhs.association)
			   == static_cast<int8_t>(lhs.association);
}

/* --------------------------- Относится к Token ---------------------------- */
bool token::operator==(const Token &rhs, const Token &lhs)
{
	return rhs.m_value == lhs.m_value && rhs.m_type == lhs.m_type;
}

void token::swap(Token &lhs, Token &rhs)
{
	std::swap(lhs.m_value, rhs.m_value);
	token::swap(lhs.m_type, rhs.m_type);
}

token::Token::Token(const std::string &value, const TokenType &type)
	: m_value{value}
	, m_type{type}
{
}

token::Token &token::Token::operator=(const Token &rhs) noexcept
{
	copyAndSwap(rhs);
	return *this;
}

token::Token &token::Token::operator=(const Token &&rhs) noexcept
{
	copyAndSwap(rhs);
	return *this;
}

token::Token::Token(const Token &rhs) noexcept { copyAndSwap(rhs); }

token::Token::Token(const Token &&rhs) noexcept { copyAndSwap(rhs); }

// TODO [0]: Доделать полостью createToken и протестировать
// TODO [1]: Написать соответствующие функции в utils для определения токена и
// протестировать
token::Token token::Token::createToken(const std::string &value)
{
	assert(!value.empty());

	Token result{
		"Empty", {Type::None, 0, Association::None}
	   };

	if (utils::isNumber(value))
	{
		result = Token{
			value, {Type::Number, 0, Association::None}
		   };
	}

	return result;
}

void token::Token::copyAndSwap(const Token &rhs) noexcept
{
	std::string tempStr{rhs.m_value};
	TokenType tempType{rhs.m_type.type, rhs.m_type.precedence,
					   rhs.m_type.association};

	m_value.swap(tempStr);
	token::swap(m_type, tempType);
}
