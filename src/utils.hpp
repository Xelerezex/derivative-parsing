#pragma once

#ifndef UTILS_H
#	define UTILS_H
#	include <string>
#	include <vector>

/**
 * @brief Пространство имен с функциями общего назначения
 */
namespace utils
{

/**
 * @brief Класс, отвечающий за парсинг из стрима, небольших юнитов.
 */
class UnitParser
{
public:
	explicit UnitParser(std::istream &streamToParse);

	// Деструктор
	~UnitParser() = default;

	// Удаленные конструкторы и операторы
	UnitParser() = delete;
	UnitParser(const UnitParser &) = delete;
	UnitParser(const UnitParser &&) = delete;
	UnitParser &operator=(const UnitParser &) = delete;
	UnitParser &operator=(const UnitParser &&) = delete;

public:
	/**
	 * @brief Коды ошибок, возможных при отработке класса
	 */
	enum class Error : int8_t
	{
		/** Отсутствие ошибки */
		None,
		/** Произошла ошибка при парсинге */
		ParsingError
	};

public:
	/**
	 * @brief Метод возвращает последнюю произошедшую ошибку
	 *
	 * @return Error - None, если ошибки не было, либо код
	 *         произошедшей ошибки
	 */
	[[nodiscard]] Error getLastError() const;

	/**
	 * @brief Метод парсит из стрима числовое значение
	 *
	 * @param outputNumber - спаршенное из стрима число
	 * @return Error - None, если ошибки не было, либо код
	 *         произошедшей ошибки
	 */
	[[nodiscard]] Error parseInteger(int &outputNumber);

	/**
	 * @brief Метод парсит из стрима один символ
	 *
	 * @param outputCharacter - символ, спаршенный из стрима
	 * @return Error - None, если ошибки не было, либо код
	 *         произошедшей ошибки
	 */
	[[nodiscard]] Error parseCharacter(char &outputCharacter);

private:
	/**
	 * @brief Установить код, последней произошедшей ошибки
	 *
	 * @param lastError - код последней ошибки
	 */
	void setLastError(Error lastError);

private:
	/** Стрим, из которого происходит чтение */
	std::istream &m_stream;

	/** Последняя произошедшая ошибка */
	Error m_lastError;
};

/**
 * @brief Функция разделяет строку даваемую на вход, по какомуто разделителю
 *
 * @param input - входная строка
 * @param seperator - разделитель
 * @return стандартный вектор с разделенной строкой
 */
std::vector<std::string> split(const std::string &input, char seperator);

} // namespace utils

#endif