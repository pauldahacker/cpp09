#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>

# define DATA_FILE "data.csv"

struct Data
{
	public:
		Data();
		Data(const Data &other);
		~Data();

		const Data &operator=(const Data &other);

		void loadData();
	private:
		std::map<std::string, float> _data;
};

#endif