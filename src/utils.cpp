#include "utils.hpp"

#include <istream>

std::vector<std::string> utils::split(const std::string &input, char seperator)
{
	if (input.empty())
	{
		return {};
	}

	std::vector<std::string> output;

	std::string::size_type prevPos{0};
	std::string::size_type pos{0};

	while ((pos = input.find(seperator, pos)) != std::string::npos)
	{
		std::string const subString(input.substr(prevPos, pos - prevPos));

		output.push_back(subString);

		prevPos = ++pos;
	}

	output.push_back(input.substr(prevPos, pos - prevPos));

	return output;
}

bool utils::isNumber(const std::string &inputStr)
{
	if (inputStr.empty())
	{
		return false;
	}

	auto it_begin = inputStr.begin();
	if (*inputStr.begin() == '+' || *inputStr.begin() == '-')
	{
		it_begin = std::next(it_begin);
		if (it_begin == inputStr.end())
		{
			return false;
		}
	}

	auto non_digit = std::find_if(it_begin, inputStr.end(), [] (const char &c) {
		return !std::isdigit(c);
	});

	if (*non_digit == '.')
	{
		non_digit = std::next(non_digit);
		if (non_digit == inputStr.end())
		{
			return false;
		}
	}

	non_digit = std::find_if(non_digit, inputStr.end(), [] (const char &c) {
		return !std::isdigit(c);
	});

	return non_digit == inputStr.end();
}

bool utils::isVariable(const std::string &inputStr)
{
	if (inputStr.empty() || inputStr.length() > 1)
	{
		return false;
	}

	return std::isalpha(inputStr.front());
}

bool utils::isLeftParenthesis(const std::string &inputStr)
{
	if (inputStr.empty() || inputStr.length() > 1)
	{
		return false;
	}

	return *inputStr.c_str() == '(';
}

bool utils::isRightParenthesis(const std::string &inputStr)
{
	if (inputStr.empty() || inputStr.length() > 1)
	{
		return false;
	}

	return *inputStr.c_str() == ')';
}
