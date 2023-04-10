#include "utils.hpp"

#include <istream>

utils::UnitParser::UnitParser(std::istream &streamToParse)
	: m_stream{streamToParse}
	, m_lastError{utils::UnitParser::Error::None}
{
}

utils::UnitParser::Error utils::UnitParser::getLastError() const
{
	return m_lastError;
}

utils::UnitParser::Error utils::UnitParser::parseInteger(int &outputNumber)
{
	int integer{0};

	if (!(m_stream >> integer))
	{
		setLastError(Error::ParsingError);
	}

	// Отдаем спаршеное значение
	outputNumber = integer;

	return getLastError();
}

void utils::UnitParser::setLastError(Error lastError)
{
	m_lastError = lastError;
}

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
