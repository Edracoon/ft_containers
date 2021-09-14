#include <iostream>
#include "vector.hpp"

int	main( void )
{
	// ======= RESIZE =======

	ft::vector<int> myvector(10, 3);

	// set some initial content:
	myvector.resize(5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(8,100);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(12);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(12, 10);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(100, 5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(SIZE_MAX, 5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;

	ft::vector<int>::iterator	it = myvector.begin();
	ft::vector<int>::iterator	ite = myvector.end();

	std::cout << "myvector contains:";
	for ( ; it != ite ; it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "capacity = " << myvector.capacity() << std::endl;

	// =========================== 

	// ft::vector<int>		vectint(10);
	// std::cout << "capacity = " << vectint.capacity() << std::endl; 
	// ft::vector<int>::iterator	it = vectint.begin();
	// ft::vector<int>::iterator	it_cpy = it;
	// ft::vector<int>::iterator	ite = vectint.end();
	// while (it_cpy != ite)
	// {
	// 	std::cout << *it_cpy << " ";
	// 	*it_cpy = 5;
	// 	it_cpy++;
	// }

	// ft::vector<int>::iterator	it2 = vectint.begin();
	// ft::vector<int>::iterator	ite2 = vectint.end();
	// while (it2 != ite2)
	// {
	// 	std::cout << *it2 << " ";
	// 	*it2 = 14;
	// 	it2++;
	// }

	// std::cout << "size = " << vectint.size() << std::endl;
	// ft::vector<int>::iterator	it3 = vectint.begin();
	// ft::vector<int>::iterator	ite3 = vectint.end();
	// while (it3 != ite3)
	// {
	// 	std::cout << *it3 << " ";
	// 	*it3 = 14;
	// 	it3++;
	// }
}
