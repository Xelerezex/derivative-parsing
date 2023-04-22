#include "tokentype.hpp"

#include <utility>

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