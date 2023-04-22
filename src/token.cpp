#include "token.hpp"

#include "utils.hpp"

#include <config-file.hpp>

#ifdef WHEN_DEBUG_MODE
	#define DEBUG_UNUSED(x) (void)(x);
	#include <chrono>
	#include <iostream>
	#include <thread>
	#include <utility>
#endif

// Объявление функции, из файла tokentype.hpp
void token::swap(token::TokenType &lhs, token::TokenType &rhs);

/* -------------------------------------------------------------------------- */
bool token::operator==(const Token &rhs, const Token &lhs)
{
	return rhs.m_value == lhs.m_value && rhs.m_type == lhs.m_type;
}

void token::swap(Token &lhs, Token &rhs)
{
	std::swap(lhs.m_value, rhs.m_value);
	token::swap(lhs.m_type, rhs.m_type);
}

token::Token::Token(std::string value, const TokenType &type)
	: m_value{std::move(value)}
	, m_type{type}
{
}

token::Token::Token(const Token &rhs) noexcept
	: m_value{rhs.m_value}
	, m_type{rhs.m_type}
{
}

token::Token::Token(const Token &&rhs) noexcept
	: m_value{std::move(rhs.m_value)}
	, m_type{std::move(rhs.m_type)}
{
}

token::Token &token::Token::operator=(const Token &rhs) noexcept
{
	copyAndSwap(rhs);
	return *this;
}

token::Token &token::Token::operator=(const Token &&rhs) noexcept
{
	copyAndSwap(std::move(rhs));
	return *this;
}

token::Token token::Token::createToken(const std::string &value)
{
	if (value.empty())
	{
		throw std::logic_error("Empty token string");
	}

	Token result{value, {Type::None, 0, Association::None}};

	if (utils::isNumber(value))
	{
		result = Token{value, {Type::Number, 0, Association::None}};
	}
	else if (utils::isVariable(value))
	{
		result = Token{value, {Type::Variable, 0, Association::None}};
	}
	else if (utils::isLeftParenthesis(value))
	{
		result = Token{value, {Type::LeftParenthesis, 0, Association::None}};
	}
	else if (utils::isRightParenthesis(value))
	{
		result = Token{value, {Type::RightParenthesis, 0, Association::None}};
	}
	else if (utils::isPlus(value))
	{
		result = Token{value, {Type::Plus, 1, Association::Left}};
	}
	else if (utils::isMinus(value))
	{
		result = Token{value, {Type::Minus, 1, Association::Left}};
	}
	else if (utils::isMultiplication(value))
	{
		result = Token{value, {Type::Multiplication, 2, Association::Left}};
	}
	else if (utils::isDivision(value))
	{
		result = Token{value, {Type::Division, 2, Association::Left}};
	}
	else if (utils::isExponentiation(value))
	{
		result = Token{value, {Type::Exponentiation, 3, Association::Right}};
	}

	return result;
}

void token::Token::copyAndSwap(Token rhs) noexcept
{
	m_value.swap(rhs.m_value);
	token::swap(m_type, rhs.m_type);
}
