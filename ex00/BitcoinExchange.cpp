#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &input) : _input(input)
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _input(other._input)
{}

BitcoinExchange::~BitcoinExchange()
{}

const BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_input = other._input;
	return (*this);
}

