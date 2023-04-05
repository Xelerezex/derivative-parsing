#include "token.hpp"


// TODO: Удалить это все. Либо внести в cmake.config и обернуть макросом
//       по типу DEBUG_MODE:
#define UNUSED(x) (void)x;
#include <thread>
#include <chrono>
#include <iostream>

bool token::operator==(const token::Token &rhs, const token::Token &lhs)
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

    std::cout << "WORD = " << word << std::endl;

    return result;
}

token::Error token::tokenize(std::istream &stream, std::vector<token::Token>& tokens)
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
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(200ms);

        // Проверяем следующий символ
        character = stream.peek();
        if (std::isdigit(character))
        {   
            result = parseUnit<int>(stream);
            if (result != Error::None)
            {
                return result;
            }
            tokens.push_back({Type::Number, 0, Association::None});
        }
        if(std::isspace(character))
        {
            result = parseUnit<char>(stream);
            if (result != Error::None)
            {
                return result;
            }
        } 
        else 
        {
            result = Error::UnknownToken;
        }
    }

    return result;
}
