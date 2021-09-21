#include <iostream>
#include "../vector.hpp"

int	main( void )
{
	ft::vector<int>				vecti;

	vecti.push_back(32);
	vecti.push_back(634);
	vecti.push_back(12);
	
	vecti.assign(50, 100);
	vecti.assign(4, 10);

	ft::vector<int>::iterator	it = vecti.begin();
	ft::vector<int>::iterator	ite = vecti.end();
	for ( ; it != ite ; it++)
		std::cout << " " << *it << std::endl;
	std::cout << "size = " << vecti.size() << " capacity = " << vecti.capacity() << std::endl;
}
