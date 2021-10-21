#include <iostream>
#include "../../../set.hpp"
#include "../../../vector.hpp"
#include "../common.hpp"
#include <list>

int	main(void)
{
	ft::set<int>				set;
	std::list<int>				list;
	for (int i = 0 ; i < 100 ; i++) list.push_back(i);

	std::cout << "set.insert(i) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		set.insert(i);
	
	printSizeContent(set);

	std::cout << "erase multiple element in a for :" << std::endl;
	for (int i = 0 ; i < 15 ; i++) {
		if (i % 3) {
			set.erase(i);
			std::cout << "erased key = " << i << std::endl;
		}
	}

	printSizeContent(set);

	std::cout << "set.insert(list.begin(), list.end())" << std::endl;
	set.insert(list.begin(), list.end());
	printSizeContent(set);

	std::cout << "set.erase(set.begin(), set.end())" << std::endl;
	set.erase(set.begin(), set.end());
	printSizeContent(set);

	std::cout << "set.clear()" << std::endl;
	set.clear();

	printSizeContent(set);

	return (0);
}

