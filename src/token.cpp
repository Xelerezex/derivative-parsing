#include "token.hpp"

#include <config-file.h>

#ifdef WHEN_DEBUG_MODE
#define UNUSED(x) (void)x;
#include <thread>
#include <chrono>
#include <iostream>
#endif

bool token::operator==(const token::TokenType &rhs, const token::TokenType &lhs)
{
    return static_cast<int8_t>(rhs.type) == static_cast<int8_t>(lhs.type)
        && static_cast<unsigned int>(rhs.precedence) == static_cast<unsigned int>(lhs.precedence)
        && static_cast<int8_t>(rhs.association) == static_cast<int8_t>(lhs.association);
}

/**
 * @brief Шаблонная функция, используемая только в этой единице трансляции.
 *        Нужна для парсинга целого "слова" из стрима (будь то числоЮ знак или реальное слово)
 * 
 * @tparam Type - шаблонный тип
 * @param  stream - стрим, из которого будет считываться слово
 * @return token::Error - код ошибки. Error::None - в случае успеха
 */
template<typename Type>
token::Error parseUnit(std::istream &stream)
{
    token::Error result {token::Error::None};

    Type word;
    if (!(stream >> word))
    {
        return result = token::Error::WordParsingError;
    }

    std::cout << "WORD = " << std::to_string(word) << std::endl;

    return result;
}

token::Error token::tokenize(std::istream &stream, std::vector<token::TokenType>& tokens)
{
    Error result {Error::None};
    // В случае пустой строки, выкидываем ошибку:
    if (stream.peek() == std::char_traits<char>::eof())
    {   
        return result = Error::EmptyString;
    }

    char character{0};
    while (stream.peek() != std::char_traits<char>::eof())
    {   
        // Раскомментить, если бесконечный цикл
        // using namespace std::chrono_literals;
        // std::this_thread::sleep_for(200ms);

        // Проверяем следующий символ
        character = stream.peek();
        // Выкидываем пробелы из стрима
        if(std::isspace(character))
        {   
            char space;
            stream.get(space);
            continue;
        } 

        if (std::isdigit(character))
        {   
            result = parseUnit<int>(stream);
            if (result != Error::None)
            {
                return result;
            }
            tokens.push_back({Type::Number, 0, Association::None});
        }
        else 
        {
            result = Error::UnknownToken;
        }
    }

    return result;
}
