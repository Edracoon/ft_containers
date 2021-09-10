#include <iostream>
#include "vector.hpp"

int	main( void )
{
	ft::vector<int>		vectint(10, 15);

	ft::vector<int>::iterator	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		it++;
	}
}
