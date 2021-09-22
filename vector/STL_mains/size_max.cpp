#include <iostream>
#include <vector>

void test11( void )
{
	std::cout << "==== SIZE_MAX ====" << std::endl;
	std::vector<int>				vecti;
	std::vector<double>				vectd;
	std::vector<char>				vectc;
	std::vector<std::string>		vects;

	std::cout << "int \t" << vecti.max_size() << std::endl;
	std::cout << "double \t" << vectd.max_size() << std::endl;
	std::cout << "char \t" << vectc.max_size() << std::endl;
	std::cout << "string \t" << vects.max_size() << std::endl;
}

int	main(void)
{
	test11();
}