#include <iostream>
#include <vector>

void test4( void )
{
	std::cout << "==== FRONT_BACK_AT ====" << std::endl;
	std::vector<int>				vecti;

	vecti.push_back(12);
	vecti.push_back(42);
	vecti.push_back(67);

	std::cout << "front = " << vecti.front() << std::endl;
	std::cout << "back = " << vecti.back() << std::endl;
	
	vecti.push_back(12973);

	std::cout << "front = " << vecti.front() << std::endl;
	std::cout << "back = " << vecti.back() << std::endl;
	
	std::cout << "at[0] = " << vecti.at(0) << std::endl;
	std::cout << "at[1] = " << vecti.at(1) << std::endl;
	std::cout << "at[2] = " << vecti.at(2) << std::endl;
	std::cout << "at[3] = " << vecti.at(3) << std::endl;

	std::vector<int>::iterator	it = vecti.begin();
	std::vector<int>::iterator	ite = vecti.end();
	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl << "size = " << vecti.size() << " capacity = " << vecti.capacity() << std::endl;
}

int	main(void)
{
	test4();
}