#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define DATA_FILE "data.csv"
# include "Utils.hpp"

typedef std::map<std::string, float> Data;

struct BitcoinExchange
{
	public:
		// exceptions
		class UnreadableInputException;
		class BadInputException;
		class TooOldException;
		class InvalidValueInputException;

		static void display(const char *input);
	private:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		BitcoinExchange &operator=(const BitcoinExchange &other);

		static Data 		loadData();
		static bool 		isTooOld(const std::string &date, const Data &data);
		static const float 	&findRate(const std::string &date, const Data &data);
		static void 		displayLine(const std::string &line, const Data &data);
};

#endif