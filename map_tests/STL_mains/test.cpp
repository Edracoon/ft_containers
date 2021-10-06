#include <iostream>
#include <map>

int	main(void)
{
	std::map<std::string,  int>	map_test;

	map_test.insert(std::make_pair("20", 4));
	map_test.insert(std::make_pair("15", 5));
	map_test.insert(std::make_pair("25", 4));
	map_test.insert(std::make_pair("22", 7));
	map_test.insert(std::make_pair("26", 8));
	map_test.insert(std::make_pair("12", 4));
	map_test.insert(std::make_pair("17", 4));
	map_test.insert(std::make_pair("4", 4));
	//map_test.print_tree();

	std::map<std::string,  int>::iterator	it = map_test.begin();
	std::map<std::string, int>::iterator		ite = map_test.end();

	std::cout << "Begin : [" << it->first << " - " << it->second << "]" << std::endl;
	std::cout << "End : [" << ite->first << " - " << ite->second << "]" << std::endl;
	return (0);
}