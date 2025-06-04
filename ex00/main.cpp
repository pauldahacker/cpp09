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
			std::cerr << e.what() << std::endl;
		}
	}
	if (argc != 2)
		std::cerr << "Too few or too many arguments" << std::endl;
	return (0);
}