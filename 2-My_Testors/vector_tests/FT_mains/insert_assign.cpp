#include <iostream>
#include "../../../vector.hpp"

void test5( void )
{
	std::cout << "==== INSERT_ASSIGN ====" << std::endl;
	ft::vector<int>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back(i);
	
	ft::vector<int>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;
	vectint.insert(it, 3, 800);

	ft::vector<int>				vectint_2;
	//vectint_2 = vectint;
	vectint_2.assign(vectint.begin(), vectint.end());
	std::cout << "vectint_2.capacity() = " << vectint_2.capacity() << " vectint_2.size() = " << vectint_2.size() << std::endl;

	ft::vector<int>::iterator	it2 = vectint_2.begin();
	for (int i = 0 ; i < 10 ; i++)
		it2++;

	vectint_2.insert(it2, vectint.begin(), vectint.end());
	
	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();
	for ( ; it != ite ; it++ )
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "vectint.capacity() = " << vectint.capacity() << " vectint.size() = " << vectint.size() << std::endl;

	it = vectint.begin();
	ite = vectint.end();
	for ( ; it != ite ; it++ )
		std::cout << *it << " ";
	std::cout << std::endl;
}

int	main(void)
{
	test5();
}
