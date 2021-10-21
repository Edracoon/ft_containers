#include <iostream>
#include "../../../map.hpp"
#include "../../../vector.hpp"
#include "../common.hpp"

int	main(void)
{
	ft::map<int, std::string>							map;
	ft::vector<ft::pair<int, std::string> >				vec;
	map.get_allocator();
	for (int i = 0 ; i < 100 ; i++) vec.push_back(ft::make_pair(i, "e"));

	std::cout << "map.insert(ft::make_pair(i, 'oui')) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		map.insert(ft::make_pair(i, "oui"));
	
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