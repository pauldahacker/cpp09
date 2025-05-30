#include "Data.hpp"

Data::Data()
{
	try
	{
		loadData();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Data::Data(const Data &other) : _data(other._data)
{}

Data::~Data()
{}

const Data &Data::operator=(const Data &other)
{
	if (this != &other)
		_data = other._data;
}

void Data::loadData()
{
	std::string line;
	std::ifstream dataFile(DATA_FILE);
	if (dataFile.is_open())
	{
		while (std::getline(dataFile, line))
		{
			int pos = line.find(",");
			_data[line.substr(0, pos)] = std::strtof(line.substr(pos + 1).c_str(), 0);
		}
	}
	else
		throw (std::ios_base::failure("Unable to open data file"));
}