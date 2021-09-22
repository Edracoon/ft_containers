#include <iostream>
#include <vector>

void test6( void )
{
	std::cout << "==== INSERT ====" << std::endl;
	std::vector<std::string>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back("test");

	std::vector<std::string>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;

	vectint.insert(it, 3, "coucou");

	std::cout << " vectint.capacity() = " << vectint.capacity() << " vectint.size() = " << vectint.size() << std::endl;

	std::vector<std::string>				vectintcpy;

	vectintcpy = vectint;
	std::cout << "assignation vector" << std::endl;
	std::cout << " vectintcpy.capacity() = " << vectintcpy.capacity() << " vectintcpy.size() = " << vectintcpy.size() << std::endl;

	it = vectint.begin();
	std::vector<std::string>::iterator	ite = vectint.end();
	for ( ; it != ite ; it++ )
		std::cout << *it << " ";
	std::cout << std::endl;
}

int	main(void)
{
	test6();
}