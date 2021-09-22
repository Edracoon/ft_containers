#include <iostream>
#include "../vector.hpp"

void	test12(void)
{
	ft::vector<int>		vectint;

	for (int i = 0 ; i < 20 ; i++)
		vectint.push_back(42);

	ft::vector<int>		range = ft::vector<int>(vectint.begin(), vectint.end());

	ft::vector<int>::iterator	it = range.begin();
	ft::vector<int>::iterator	ite = range.end();

	for ( ; it != ite ; it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "vectint.size = " << vectint.size() << " vectint.capacity() = " << vectint.capacity() << std::endl;
	std::cout << "range.size = " << range.size() << " range.capacity() = " << range.capacity() << std::endl;

	std::cout << "vectint.begin() = " << *(vectint.begin()) << " vectint.end() = " << *(vectint.end()) << std::endl;
	std::cout << "range.begin() = " << *(range.begin()) << " range.end() = " << *(range.end()) << std::endl;
}

int	main(void)
{
	test12();
}