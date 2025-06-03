#include "BitcoinExchange.hpp"

class BitcoinExchange::UnreadableInputException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("could not open input file.");
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

const Data &BitcoinExchange::getData() const
{
	return (this->_data);
}

bool BitcoinExchange::isDateValid(const std::string &date) const
{
	std::tm tm = {};

	size_t pos1 = date.find("-");
	if (pos1 == date.npos)
		return (false);
	std::string monthStr = date.substr(pos1 + 1);
	size_t pos2 = monthStr.find("-");
	if (pos2 == date.npos)
		return (false);
	std::string dayStr = monthStr.substr(pos2 + 1);
	if (!isInt(date) || !isInt(monthStr) || !isInt(dayStr))
		return (false);
	int year = std::atoi(date.c_str());
	int month = std::atoi(monthStr.c_str());
	int day = std::atoi(dayStr.c_str());
	tm.tm_year = year - 1900;
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	std::time_t temp = std::mktime(&tm);
	if (temp == -1 || tm.tm_year != year - 1900 || tm.tm_mon != month - 1 || tm.tm_mday != day)
		return (false);
	return (!_data.isTooOld(date));
}

/*
https://en.cppreference.com/w/cpp/chrono/c/tm.html
https://en.cppreference.com/w/cpp/chrono/c/mktime
*/
void BitcoinExchange::displayLine(const std::string &line) const
{
	size_t pos = line.find(" | ");
	if (pos == line.npos)
		throw (BadInputException(line));
	std::string date = line.substr(0, pos + 1);
	if (!isDateValid(date) || pos == line.npos)
		throw (BadInputException(line));
	if (!isFloat(line.substr(pos + 3)))
		throw (InvalidValueInputException("not a valid float."));
	float inputVal = convertToFloat(line.substr(pos + 3));
	if (inputVal < 0.0)
		throw (InvalidValueInputException("not a positive number."));
	if (inputVal > 1000.0)
		throw (InvalidValueInputException("too large a number."));
	std::cout << date << " => " << _data.findRate(date) * inputVal << std::endl;
}

void BitcoinExchange::display() const
{
	std::string line;
	std::ifstream inputFile(_input);

	if (inputFile.is_open())
	{
		std::getline(inputFile, line);
		while (std::getline(inputFile, line))
		{
			try
			{
				displayLine(line);
			}
			catch(const std::exception& e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
	}
	else
		throw (UnreadableInputException());
}