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
