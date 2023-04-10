#include "token.hpp"

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

/**
 * @brief Шаблонная функция, используемая только в этой единице трансляции.
 *        Нужна для парсинга целого "слова" из стрима (будь то числоЮ знак или
 * реальное слово)
 *
 * @tparam Type - шаблонный тип
 * @param  stream - стрим, из которого будет считываться слово
 * @param  output - спаршенное строковое значение
 * @return token::Error - код ошибки. Error::None - в случае успеха
 */
template <typename Type>
token::Error parseUnit(std::istream &stream, std::string &output)
{
	token::Error result{token::Error::None};

	Type word;
	if (!(stream >> word))
	{
		return result = token::Error::WordParsingError;
	}

	// Если тип является строкой, его не надо приводить к строке
	if constexpr (std::is_same_v<Type, std::string>)
	{
		output = word;
	}
	else
	{
		output = std::to_string(word);
	}

#ifdef WHEN_DEBUG_MODE
	std::cout << "WORD = " << output << std::endl;
#endif

	return result;
}

// TODO: Move parser to new class to utils.h
token::Error token::tokenize(std::istream &stream,
							 std::vector<token::Token> &tokens)
{
	Error result{Error::None};
	// В случае пустой строки, выкидываем ошибку:
	if (stream.peek() == std::char_traits<char>::eof())
	{
		return Error::EmptyString;
	}

	char character{0};
	while (stream.peek() != std::char_traits<char>::eof())
	{
		// Раскомментить, при дебаге бесконечного цикла
		// using namespace std::chrono_literals;
		// std::this_thread::sleep_for(200ms);

		// Проверяем следующий символ
		character = static_cast<char>(stream.peek());
		// Выкидываем пробелы из стрима
		if (std::isspace(character) != 0)
		{
			char space = 0;
			stream.get(space);
			continue;
		}

		if (std::isdigit(character) != 0) // Если встреченный символ - число
		{
			std::string number;

			// Парсим числовое значение
			result = parseUnit<int>(stream, number);
			if (result != Error::None)
			{
				return result;
			}

			// При успешном парсинге - добавляем его к остальным токенам
			tokens.push_back({
				number, {Type::Number, 0, Association::None}
			});
		}
		else if (std::isalpha(character) != 0) // Если встреченный символ -
											   // переменная (буква)
		{
			std::string alphabetic;

			// Парсим буквенное значение
			result = parseUnit<std::string>(stream, alphabetic);
			if (result != Error::None)
			{
				return result;
			}

			// При успешном парсинге - добавляем его к остальным токенам
			tokens.push_back({
				alphabetic, {Type::Variable, 0, Association::None}
			  });
		}
		else
		{
			return Error::UnknownToken;
		}
	}

	return result;
}
