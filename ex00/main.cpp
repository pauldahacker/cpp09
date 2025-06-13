#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
		std::cerr << "Error: Too few or too many arguments" << std::endl;
	else
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
	return (0);
}