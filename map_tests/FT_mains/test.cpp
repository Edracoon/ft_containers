#include <iostream>
#include "../../map.hpp"

int	main(void)
{
	ft::map<std::string,  int>	map_test;

	map_test.insert(ft::make_pair("5", 10));
	map_test.insert(ft::make_pair("3", 10));
	map_test.insert(ft::make_pair("7", 10));
	map_test.insert(ft::make_pair("2", 10));
	map_test.insert(ft::make_pair("4", 10));
	map_test.insert(ft::make_pair("6", 10));
	map_test.insert(ft::make_pair("8", 10));
	map_test.insert(ft::make_pair("9", 10));

	map_test.print_tree();

	ft::map<std::string, int>::iterator		it = map_test.begin();
	ft::map<std::string, int>::iterator		ite = map_test.end();
	for ( ; it != ite ; ++it)
		std::cout << "it = [" << it->first << " - " << it->second << "]" << std::endl;
	it = map_test.begin();
	for ( ; it != ite ; ) {
		--ite;
		std::cout << "ite = [" << ite->first << " - " << ite->second << "]" << std::endl;
	}
	std::cout << "map.clear()" << std::endl;
	map_test.clear();
	std::cout << "map.empty() -> " << map_test.empty() << std::endl;
	std::cout << "print_tree()" << std::endl;
	map_test.print_tree();
	return (0);
}