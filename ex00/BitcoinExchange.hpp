#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include "Data.hpp"

struct Data;
struct BitcoinExchange
{
	public:
		BitcoinExchange(const std::string &input);
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		const BitcoinExchange &operator=(const BitcoinExchange &other);

		// exceptions
		class UnreadableInputException;
		class BadInputException;
		class InvalidValueInputException;

		// member functions
		const Data &getData() const;
		bool isDateValid(const std::string &line) const;
		void displayLine(const std::string &line) const;
		void display() const;
	private:
		std::string _input;
		Data		_data;
};

#endif