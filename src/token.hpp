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
    Variable = 0,

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

bool operator==(const Token &rhs, const Token &lhs);

/**
 * @brief Функция токенезирует текст из стрима
 * 
 * @param stream 
 * @param tokens 
 * @return int 
 */
int tokenize(std::istream& stream, std::vector<Token> tokens);

}

#endif