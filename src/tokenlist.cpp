#include "tokenlist.hpp"

#include "utils.hpp"

token::TokenList::Error token::TokenList::tokenizer(const std::string &inputStr,
													TokensList &outputTokens)
{
	Error errorCode{Error::None};

	DEBUG_UNUSED(outputTokens);

	if (inputStr.empty())
	{
		errorCode = Error::EmptyString;
	}

	outputTokens = m_tokens;

	return errorCode;
}
