#pragma once

#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <cstdint>
#include <istream>
#include <vector>

/// @brief Пространство имен для основного класса Токена и сопутствующих функций
namespace token
{

/**
 * @brief Перечислитель с типом токена. 
 * 
 */
enum class Type : int8_t
{   
    /** Число. */
    Number = 0,

    /** Математическая переменная. */
    Variable,

    /** Левая круглая скобка. */
    LeftParenthesis,

    /** Правая круглая скобка. */
    RightParenthesis
};

/**
 * @brief Перечислитель со свойством ассоциативности токена.
 * 
 */
enum class Association : int8_t
{   
    /** Отсутствие ассоциативности. */
    None = 0,

    /** Левая ассоциативность. */
    Left,

    /** Правая ассоциативности. */
    Right
};

/**
 * @brief Перечислитель с ошибками, встречающимися при работе
 *        с токенами
 * 
 */
enum class Error : int8_t
{   
    /** Отсутсвие ошибки. Корректная отработка */
    None = 0,

    /** Некая обычная ошибка */
    DefaultError, 
};

/**
 * @brief Структура, представлябщая собой один токен.
 * 
 */
struct Token
{
    /* Тип токена */
    Type type;

    /* Старшинство токена */
    unsigned int precedence;

    /* Ассоциативность токена */ 
    Association association;
};

/**
 * @brief Оператор проверки равенства двух токенов
 * 
 * @param rhs - Токен справа от ==
 * @param lhs - Токен слева от ==
 * @return true - Токены равны
 * @return false - Токены не равны
 */
bool operator==(const Token &rhs, const Token &lhs);

/**
 * @brief Функция токенезирует текст из стрима
 * 
 * @param stream 
 * @param tokens 
 * @return int - код ошибки
 */
Error tokenize(std::istream& stream, std::vector<Token>& tokens);

}

#endif