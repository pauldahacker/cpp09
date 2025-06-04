#include "BitcoinExchange.hpp"


class BitcoinExchange::UnreadableInputException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Input file cannot be read.");
		}
};

class BitcoinExchange::BadInputException : public std::exception
{
	private:
		std::string _msg;
	public:
		BadInputException(const std::string& line) : _msg(std::string("bad input => ") + line)
		{}
		virtual ~BadInputException() throw() {}
		virtual const char* what() const throw()
		{
			return (_msg.c_str());
		}
};

class BitcoinExchange::TooOldException : public std::exception
{
	private:
		std::string _msg;
	public:
		TooOldException(const std::string& line) : _msg(std::string("date is too old => ") + line)
		{}
		virtual ~TooOldException() throw() {}
		virtual const char* what() const throw()
		{
			return (_msg.c_str());
		}
};

class BitcoinExchange::InvalidValueInputException : public std::exception
{
	private:
		std::string _msg;
	public:
		InvalidValueInputException(const std::string& line) : _msg(line)
		{}
		virtual ~InvalidValueInputException() throw() {}
		virtual const char* what() const throw()
		{
			return (_msg.c_str());
		}
};

BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	(void)other;
}

BitcoinExchange::~BitcoinExchange()
{}

const BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	(void)other;
	return (*this);
}

/*
https://en.cppreference.com/w/cpp/chrono/c/tm.html
https://en.cppreference.com/w/cpp/chrono/c/mktime
*/
void BitcoinExchange::displayLine(const std::string &line, const Data &data)
{
	size_t pos = line.find(" | ");
	if (pos == line.npos)
		throw (BadInputException(line));

	std::string date = line.substr(0, pos);
	if (!isDateValid(date))
		throw (BadInputException(line));
	if (data.isTooOld(date))
		throw (TooOldException(line));

	std::string value = line.substr(pos + 3);
	if (!isValueValid(value))
		throw (InvalidValueInputException("not a valid value."));
	float inputVal = convertToFloat(value);
	if (inputVal < 0.0)
		throw (InvalidValueInputException("not a positive number."));
	if (inputVal > 1000.0)
		throw (InvalidValueInputException("too large a number."));
	std::cout << date << " => " << data.findRate(date) * inputVal << std::endl;
}

void BitcoinExchange::display(const char *input)
{
	Data	data;
	std::string line;
	std::ifstream inputFile(input);

	if (!inputFile.is_open())
		throw (UnreadableInputException());
	std::getline(inputFile, line);
	while (std::getline(inputFile, line))
	{
		try
		{
			displayLine(line, data);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	inputFile.close();
}