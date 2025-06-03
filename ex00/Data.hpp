#ifndef DATA_HPP
# define DATA_HPP

# include <fstream>
# include <map>
# include "Utils.hpp"

# define DATA_FILE "data.csv"

struct Data
{
	public:
		Data();
		Data(const Data &other);
		~Data();

		const Data &operator=(const Data &other);

		// exceptions
		class UnreadableDataException;
		class MissingCommaDataException;
		class InvalidValueDataException;

		// member functions
		void loadData();
		bool isTooOld(const std::string &date) const;
		float findRate(const std::string &date) const;
		void printData() const;
	private:
		std::map<std::string, float> _content;
};

#endif