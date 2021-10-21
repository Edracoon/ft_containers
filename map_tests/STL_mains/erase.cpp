#include <iostream>
#include <map>
#include <vector>
#include "../common.hpp"
#include <list>

int	main(void)
{
	std::map<int, std::string>							map;
	std::list<std::pair<int, std::string> >				list;
	for (int i = 0 ; i < 100 ; i++) list.push_back(std::make_pair(i, "e"));

	std::cout << "map.insert(std::make_pair(i, 'oui')) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		map.insert(std::make_pair(i, "oui"));
	
	printSizeContent(map);

	std::cout << "erase multiple element in a for :" << std::endl;
	for (int i = 0 ; i < 15 ; i++) {
		if (i % 3) {
			map.erase(i);
			std::cout << "erased key = " << i << std::endl;
		}
	}

	printSizeContent(map);

	std::cout << "map.insert(list.begin(), list.end())" << std::endl;
	map.insert(list.begin(), list.end());
	printSizeContent(map);

	std::cout << "map.erase(map.begin(), map.end())" << std::endl;
	map.erase(map.begin(), map.end());
	printSizeContent(map);

	std::cout << "map.clear()" << std::endl;
	map.clear();

	printSizeContent(map);

	return (0);
}