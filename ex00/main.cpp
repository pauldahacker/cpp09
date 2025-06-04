#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		try
		{
			BitcoinExchange::display(argv[1]);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	else
		std::cerr << "Too few or too many arguments" << std::endl;
	return (0);
}