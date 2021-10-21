#include <iostream>
#include <map>
#include <vector>
#include "../common.hpp"

int	main(void)
{
	std::map<int, std::string>								map;
	std::vector<std::pair<int, std::string> >				vec;
	for (int i = 0 ; i < 100 ; i++) vec.push_back(std::make_pair(i, "e"));

	std::cout << "map.insert(std::make_pair(i, 'oui')) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		map.insert(std::make_pair(i, "oui"));
	
	printSizeContent(map);

	std::cout << "map.clear()" << std::endl;
	map.clear();
	std::cout << "map.insert(vec.begin(), vec.end())" << std::endl;
	map.insert(vec.begin(), vec.end());

	printSizeContent(map);

	std::cout << "map.clear()" << std::endl;
	map.clear();

	printSizeContent(map);

	return (0);
}