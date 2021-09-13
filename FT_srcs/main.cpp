#include <iostream>
#include "vector.hpp"

int	main( void )
{
	ft::vector<int> myvector(10, 3);

	// set some initial content:

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	ft::vector<int>::iterator	it = myvector.begin();
	ft::vector<int>::iterator	ite = myvector.end();

	std::cout << "myvector contains:";
	for ( ; it != ite ; it++)
		std::cout << ' ' << *it;
	std::cout << '\n';
	// ft::vector<int>		vectint(10);
	// std::cout << "capacity = " << vectint.capacity() << std::endl; 
	// ft::vector<int>::iterator	it = vectint.begin();
	// ft::vector<int>::iterator	it_cpy = it;
	// ft::vector<int>::iterator	ite = vectint.end();
	// while (it_cpy != ite)
	// {
	// 	std::cout << *it_cpy << std::endl;
	// 	*it_cpy = 5;
	// 	it_cpy++;
	// }
	// ft::vector<int>::iterator	it2 = vectint.begin();
	// ft::vector<int>::iterator	ite2 = vectint.end();
	// while (it2 != ite2)
	// {
	// 	std::cout << *it2 << std::endl;
	// 	*it2 = 14;
	// 	it2++;
	// }
	// std::cout << "size = " << vectint.size() << std::endl;

	// ft::vector<int>::iterator	it3 = vectint.begin();
	// ft::vector<int>::iterator	ite3 = vectint.end();
	// while (it3 != ite3)
	// {
	// 	std::cout << *it3 << std::endl;
	// 	*it3 = 14;
	// 	it3++;
	// }
	
}
