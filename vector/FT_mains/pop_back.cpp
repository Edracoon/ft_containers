#include <iostream>
#include "../vector.hpp"

int	main( void )
{
	std::cout << "==== POP_BACK ====" << std::endl;
	// ==== POP_BACK ====
	ft::vector<int>	vectint;

	vectint.push_back(123);
	vectint.push_back(321);
	vectint.push_back(789);
	vectint.push_back(987);
	vectint.push_back(567);

	// vectint.resize(4);

	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	// vectint.pop_back();
	// std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	// // un pop_back de trop -> size 0 - 1;

	// segfault car iteration sans limite
	ft::vector<int>::iterator	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();

	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}
