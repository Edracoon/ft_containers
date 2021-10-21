#include <iostream>
#include "../../../map.hpp"
#include "../../../vector.hpp"
#include "../common.hpp"
#include <list>

int	main(void)
{
	ft::map<int, std::string>							map;
	std::list<ft::pair<int, std::string> >				list;
	for (int i = 0 ; i < 100 ; i++) list.push_back(ft::make_pair(i, "e"));

	std::cout << "map.insert(ft::make_pair(i, 'oui')) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		map.insert(ft::make_pair(i, "oui"));
	
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

