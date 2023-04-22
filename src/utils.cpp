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

	auto non_digit =
		std::find_if(it_begin, inputStr.end(), [] (const char &chr) {
			return !static_cast<bool>(std::isdigit(chr));
		});

	if (*non_digit == '.')
	{
		non_digit = std::next(non_digit);
		if (non_digit == inputStr.end())
		{
			return false;
		}
	}

	non_digit = std::find_if(non_digit, inputStr.end(), [] (const char &chr) {
		return !static_cast<bool>(std::isdigit(chr));
	});

	return non_digit == inputStr.end();
}

bool utils::isVariable(const std::string &inputStr)
{
	if (inputStr.empty() || inputStr.length() > 1)
	{
		return false;
	}

	return static_cast<bool>(std::isalpha(inputStr.front()));
}

/**
 * @brief Функция проверяет, что входящая строка не пуста и имеет только
 *        одну букву, и, что эта буква равно символу
 *
 * @param inputStr - строка на вход
 * @param symbol - символ для сравнения
 * @return true - строка имеет тоже значение, что и символ
 * @return false - строка имеет отличное от символа значение
 */
bool isSymbol (const std::string &inputStr, char symbol)
{
	if (inputStr.empty() || inputStr.length() > 1)
	{
		return false;
	}

	return *inputStr.c_str() == symbol;
}

bool utils::isLeftParenthesis(const std::string &inputStr)
{
	return isSymbol(inputStr, '(');
}

bool utils::isRightParenthesis(const std::string &inputStr)
{
	return isSymbol(inputStr, ')');
}

bool utils::isPlus(const std::string &inputStr)
{
	return isSymbol(inputStr, '+');
}

bool utils::isMinus(const std::string &inputStr)
{
	return isSymbol(inputStr, '-');
}

bool utils::isMultiplication(const std::string &inputStr)
{
	return isSymbol(inputStr, '*');
}

bool utils::isDivision(const std::string &inputStr)
{
	return isSymbol(inputStr, '/');
}

bool utils::isExponentiation(const std::string &inputStr)
{
	return isSymbol(inputStr, '^');
}

bool utils::isSpace(const std::string &inputStr)
{
	return isSymbol(inputStr, ' ');
}
