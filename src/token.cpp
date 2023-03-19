#include "token.hpp"

#define UNUSED(x) (void)x;

bool token::operator==(const token::Token &rhs, const token::Token &lhs)
{
    return rhs.type == lhs.type
        && rhs.precedence == lhs.precedence
        && rhs.association == lhs.association;
}

int token::tokenize(std::istream &stream, std::vector<token::Token> tokens)
{
    UNUSED(stream);
    UNUSED(tokens);
    
    return 0;
}
