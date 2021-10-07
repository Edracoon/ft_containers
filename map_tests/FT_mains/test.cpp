#include <iostream>
#include "../../map.hpp"

int	main(void)
{
	ft::map<std::string,  int>	map_test;

	std::cout << "hello1" << std::endl;
	map_test.insert(ft::make_pair("5", 10));
	std::cout << "hello2" << std::endl;
	map_test.insert(ft::make_pair("3", 10));
	std::cout << "hello3" << std::endl;
	map_test.insert(ft::make_pair("7", 10));
	std::cout << "hello4" << std::endl;
	map_test.insert(ft::make_pair("2", 10));
	std::cout << "hello5" << std::endl;
	map_test.insert(ft::make_pair("4", 10));
	std::cout << "hello6" << std::endl;
	map_test.insert(ft::make_pair("6", 10));
	std::cout << "hello7" << std::endl;
	map_test.insert(ft::make_pair("8", 10));
	std::cout << "hello8" << std::endl;
	map_test.insert(ft::make_pair("9", 10));
	map_test.insert(ft::make_pair("5", 10));

	map_test.print_tree();

	ft::map<std::string,  int>::iterator	it = map_test.begin();
	ft::map<std::string, int>::iterator		ite = map_test.end();
	std::cout << "BEGIN		: [" << it->first << " - " << it->second << "]" << std::endl;
	// for ( ; it != ite ; ) {
	// 	std::cout << "it++ => [" << it->first << " - " << it->second << "]" << std::endl;
	// 	it++;
	// }
	return (0);
}