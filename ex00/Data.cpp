#include "Data.hpp"

class Data::UnreadableDataException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Data file cannot be read");
		}
};

class Data::MissingCommaDataException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Data file contains a line missing a comma");
		}
};

class Data::InvalidDateDataException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Data file contains an invalid date");
		}
};

class Data::InvalidValueDataException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Data file contains an invalid value");
		}
};

Data::Data()
{
	loadData();
}

Data::Data(const Data &other) : _content(other._content)
{}

Data::~Data()
{}

const Data &Data::operator=(const Data &other)
{
	if (this != &other)
		_content = other._content;
	return (*this);
}

void Data::loadData()
{
	std::string line;
	std::ifstream dataFile(DATA_FILE);

	if (dataFile.is_open())
	{
		std::getline(dataFile, line);
		while (std::getline(dataFile, line))
		{
			size_t pos = line.find(",");
			if (pos == line.npos)
				throw (MissingCommaDataException());
			if (!isDateValid(line.substr(0, pos)))
				throw (InvalidDateDataException());
			if (!isValueValid(line.substr(pos + 1)))
				throw (InvalidValueDataException());
			_content[line.substr(0, pos)] = convertToFloat(line.substr(pos + 1));
		}
	}
	else
		throw (UnreadableDataException());
}

bool Data::isTooOld(const std::string &date) const
{
	return (_content.begin()->first > date);
}

/*
https://en.cppreference.com/w/cpp/container/map/lower_bound.html
*/
float Data::findRate(const std::string &date) const
{
	std::map<std::string, float>::const_iterator it = _content.lower_bound(date);
	if (it != _content.end() && it->first == date)
		return it->second;
	if (it != _content.begin())
		--it;
	return (it->second);
}
