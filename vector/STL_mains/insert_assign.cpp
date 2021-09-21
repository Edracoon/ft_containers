#include <iostream>
#include <vector>

int	main( void )
{
	std::vector<int>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back(i);
	
	std::vector<int>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;
	vectint.insert(it, 3, 800);

	std::vector<int>				vectint_2;
	//vectint_2 = vectint;
	vectint_2.assign(vectint.begin(), vectint.end());
	std::cout << "vectint_2.capacity() = " << vectint_2.capacity() << " vectint_2.size() = " << vectint_2.size() << std::endl;

	std::vector<int>::iterator	it2 = vectint_2.begin();
	for (int i = 0 ; i < 10 ; i++)
		it2++;

	vectint_2.insert(it2, vectint.begin(), vectint.end());
	
	it = vectint.begin();
	std::vector<int>::iterator	ite = vectint.end();
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
