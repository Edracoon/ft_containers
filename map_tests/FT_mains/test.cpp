#include <iostream>
#include "../../map.hpp"

int	main(void)
{
	ft::map<int, std::string>	map_test;

	map_test.insert(ft::make_pair(1, "cou"));
	map_test.insert(ft::make_pair(2, "qwe"));
	map_test.insert(ft::make_pair(3, "haha"));
	map_test.insert(ft::make_pair(4, "noob"));
	map_test.insert(ft::make_pair(5, "red"));
	map_test.insert(ft::make_pair(6, "black"));
	map_test.insert(ft::make_pair(7, "tree"));
	map_test.insert(ft::make_pair(8, "hello"));
	map_test.insert(ft::make_pair(8, "hihi"));
	map_test.insert(ft::make_pair(8, "hohoho"));
	map_test.insert(ft::make_pair(9, "azerty"));

	map_test.print_tree();

	// std::cout << " map_test.size() = " << map_test.size() << std::endl;

	// ft::map<int, std::string>::iterator	it = map_test.begin();
	// ft::map<int, std::string>::iterator	ite = map_test.end();

	// for ( ; it != ite ; ++it)
	// 	std::cout << "it = [" << it->first << " - " << it->second << "]" << std::endl;

	return (0);
}