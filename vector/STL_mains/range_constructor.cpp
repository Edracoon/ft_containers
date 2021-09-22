#include <iostream>
#include <vector>

void	test12(void)
{
	std::vector<int>		vectint;

	for (int i = 0 ; i < 20 ; i++)
		vectint.push_back(42);
	
	std::vector<int>		range = std::vector<int>(vectint.begin(), vectint.end());

	std::vector<int>::iterator	it = range.begin();
	std::vector<int>::iterator	ite = range.end();

	for ( ; it != ite ; it++ )
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