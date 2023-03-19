#include "token.hpp"

#define UNUSED(x) (void)x;

bool token::operator==(const token::Token &rhs, const token::Token &lhs)
{
    return static_cast<int8_t>(rhs.type) == static_cast<int8_t>(lhs.type)
        && static_cast<unsigned int>(rhs.precedence) == static_cast<unsigned int>(lhs.precedence)
        && static_cast<int8_t>(rhs.association) == static_cast<int8_t>(lhs.association);
}

token::Error token::tokenize(std::istream &stream, std::vector<token::Token>& tokens)
{
    UNUSED(stream);
    UNUSED(tokens);
    
    return Error::None;
}
