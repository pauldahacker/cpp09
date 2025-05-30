#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include "Data.hpp"

struct BitcoinExchange
{
	public:
		BitcoinExchange(const std::string &input);
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		const BitcoinExchange &operator=(const BitcoinExchange &other);

		// member functions
		void loadData();
	private:
		std::string _input;
		Data		_data;
};

#endif