#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
		std::cerr << "Too few or too many arguments" << std::endl;
	else
	{
		try
		{
			BitcoinExchange b(argv[1]);
			b.display();
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
	return (0);
}