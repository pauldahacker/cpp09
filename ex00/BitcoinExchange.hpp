#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include "Data.hpp"

struct Data;
struct BitcoinExchange
{
	public:
		// exceptions
		class UnreadableInputException;
		class BadInputException;
		class TooOldException;
		class InvalidValueInputException;

		// member functions
		static void displayLine(const std::string &line, const Data &data);
		static void display(const char *input);
	private:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		const BitcoinExchange &operator=(const BitcoinExchange &other);
};

#endif