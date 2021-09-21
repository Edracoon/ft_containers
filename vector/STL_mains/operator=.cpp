#include <iostream>
#include <vector>

int	main( void )
{
	std::vector<int>				vecti;

	vecti.push_back(12);
	vecti.push_back(42);
	vecti.push_back(67);
	vecti.push_back(67);
	vecti.push_back(345);
	vecti.push_back(67);

	vecti.reserve(10);

	std::cout << std::endl << "vecti.size = " << vecti.size() << " vecti.capacity = " << vecti.capacity();
	
	std::vector<int>				vecty;

	vecty = vecti;

	std::cout << std::endl;

	std::vector<int>::iterator	it = vecty.begin();
	std::vector<int>::iterator	ite = vecty.end();
	for ( ; it != ite ; it++)
		std::cout << *it << " ";
	std::cout << std::endl << "vecty.size = " << vecty.size() << " vecty.capacity = " << vecty.capacity();
	std::cout << std::endl << "vecti.size = " << vecti.size() << " vecti.capacity = " << vecti.capacity() << std::endl;
}