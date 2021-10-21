#include <iostream>
#include <vector>

void test1( void )
{
	std::cout << "==== ASSIGN ====" << std::endl;
	std::vector<int>				vecti;

	vecti.push_back(32);
	vecti.push_back(634);
	vecti.push_back(12);
	
	vecti.assign(50, 100);
	vecti.assign(4, 10);

	std::vector<int>::iterator	it = vecti.begin();
	std::vector<int>::iterator	ite = vecti.end();
	for ( ; it != ite ; it++)
		std::cout << " " << *it << std::endl;
	std::cout << "size = " << vecti.size() << " capacity = " << vecti.capacity() << std::endl;
}


int	main( void )
{
	test1();
}