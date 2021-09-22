#include <iostream>
#include <vector>

void test3( void )
{
	std::cout << "==== CLEAR ====" << std::endl;
	std::vector<int>	vectint;

	for (int i = 0 ; i < 10 ; i++)
		vectint.push_back(i);
	
	std::cout << "size before clear = " << vectint.size() << std::endl;

	std::cout << "is empty ? " << vectint.empty() << std::endl;

	vectint.clear();

	std::cout << "size after clear = " << vectint.size() << std::endl;

	vectint.clear();

	std::cout << "is empty ? " << vectint.empty() << std::endl;
}

int	main(void)
{
	test3();
}