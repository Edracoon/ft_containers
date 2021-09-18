#include <iostream>
#include "vector.hpp"

int	main( void )
{
	ft::vector<int>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back(i);
	
	ft::vector<int>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;
	
	vectint.insert(it, 3, 800);

	std::cout << " vectint.capacity() = " << vectint.capacity() << " vectint.size() = " << vectint.size() << std::endl;

	ft::vector<int>				vectintcpy;

	vectintcpy = vectint; std::cout << "assignation vector" << std::endl;
	std::cout << " vectintcpy.capacity() = " << vectintcpy.capacity() << " vectintcpy.size() = " << vectintcpy.size() << std::endl;

	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();
	for ( ; it != ite ; it++ )
		std::cout << *it << " ";
	std::cout << std::endl;
}
