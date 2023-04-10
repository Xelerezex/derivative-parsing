#include "token.hpp"

#include "utils.hpp"

#include <config-file.hpp>

#ifdef WHEN_DEBUG_MODE
#	define DEBUG_UNUSED(x) (void) (x);
#	include <chrono>
#	include <iostream>
#	include <thread>
#endif

bool token::operator==(const token::TokenType &rhs, const token::TokenType &lhs)
{
	return static_cast<int8_t>(rhs.type) == static_cast<int8_t>(lhs.type)
		&& static_cast<unsigned int>(rhs.precedence)
			   == static_cast<unsigned int>(lhs.precedence)
		&& static_cast<int8_t>(rhs.association)
			   == static_cast<int8_t>(lhs.association);
}

bool token::operator==(const Token &rhs, const Token &lhs)
{
	return rhs.value == lhs.value && rhs.type == lhs.type;
}
