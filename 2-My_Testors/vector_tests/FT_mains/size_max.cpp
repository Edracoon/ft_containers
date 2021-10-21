#include <iostream>
#include "../../../vector.hpp"

void test11( void )
{
	std::cout << "==== SIZE_MAX ====" << std::endl;
	ft::vector<int>				vecti;
	ft::vector<double>			vectd;
	ft::vector<char>			vectc;
	ft::vector<std::string>		vects;

	std::cout << "int \t" << vecti.max_size() << std::endl;
	std::cout << "double \t" << vectd.max_size() << std::endl;
	std::cout << "char \t" << vectc.max_size() << std::endl;
	std::cout << "string \t" << vects.max_size() << std::endl;
}

int	main(void)
{
	test11();
}