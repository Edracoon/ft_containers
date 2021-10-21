#include <iostream>
#include <set>
#include <vector>
#include "../common.hpp"

int	main(void)
{
	std::set<int>					set;
	std::vector<int>				vec;
	for (int i = 0 ; i < 100 ; i++) vec.push_back(i);

	std::cout << "set.insert(i) x 15" << std::endl;
	for (int i = 0 ; i < 15 ; i++)
		set.insert(i);
	
	printSizeContent(set);

	std::cout << "set.clear()" << std::endl;
	set.clear();
	std::cout << "set.insert(vec.begin(), vec.end())" << std::endl;
	set.insert(vec.begin(), vec.end());

	printSizeContent(set);

	std::cout << "set.clear()" << std::endl;
	set.clear();

	printSizeContent(set);

	return (0);
}