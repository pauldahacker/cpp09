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

/*
Returns the data from DATA_FILE in std::map<string,float> form.
if it fails, it throws a std::Exception.
*/
static Data loadData()
{
	Data data;
	std::string line;
	std::ifstream dataFile(DATA_FILE);

	if (dataFile.is_open())
	{
		std::getline(dataFile, line);
		while (std::getline(dataFile, line))
		{
			size_t pos = line.find(",");
			if (pos == line.npos)
				throw (std::runtime_error("Data file contains a line missing a comma."));
			if (!isDateValid(line.substr(0, pos)))
				throw (std::runtime_error("Data file contains an invalid date."));
			if (!isValueValid(line.substr(pos + 1)))
				throw (std::runtime_error("Data file contains an invalid value."));
			data[line.substr(0, pos)] = convertToFloat(line.substr(pos + 1));
		}
		dataFile.close();
		return (data);
	}
	else
		throw (std::ios_base::failure("Data file cannot be read."));
}

static bool isTooOld(const std::string &date, const Data &data)
{
	return (data.begin()->first > date);
}

/*
https://en.cppreference.com/w/cpp/container/map/lower_bound.html
*/
static float findRate(const std::string &date, const Data &data)
{
	Data::const_iterator it = data.lower_bound(date);
	if (it != data.end() && it->first == date)
		return it->second;
	if (it != data.begin())
		--it;
	return (it->second);
}

/*
Attempts to display a single line of input file.
if it fails, it throws a BitcoinExchange::Exception.
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
	if (isTooOld(date, data))
		throw (TooOldException(line));

	std::string value = line.substr(pos + 3);
	if (!isValueValid(value))
		throw (InvalidValueInputException("not a valid value."));
	float inputVal = convertToFloat(value);
	if (inputVal < 0.0)
		throw (InvalidValueInputException("not a positive number."));
	if (inputVal > 1000.0)
		throw (InvalidValueInputException("too large a number."));
	std::cout << date << " => " << findRate(date, data) * inputVal << std::endl;
}

/*
Attempts to display all lines in input.
if it fails, it throws an appropriate exception.
*/
void BitcoinExchange::display(const char *input)
{
	Data			data = loadData();
	std::string 	line;
	std::ifstream	inputFile(input);

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
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	inputFile.close();
}

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
