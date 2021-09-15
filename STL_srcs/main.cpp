#include <iostream>
#include <vector>

// copier les mains dans f-t_srcs/testers et change_all_occurrence [f-t] -> [std]

int	main( void )
{
		// ==== PUSH_BACK ====
	std::vector<int>	vectint;
	vectint.push_back(43);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(23);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(1);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(87);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(567);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(4);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(3453);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(123);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(4537);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(53443);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.push_back(3243);
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;

	std::vector<int>::iterator	it = vectint.begin();
	std::vector<int>::iterator	ite = vectint.end();

	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}
