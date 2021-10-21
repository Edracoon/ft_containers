#include <iostream>
#include "../../../vector.hpp"

void test10( void )
{
	std::cout << "==== RESIZE ====" << std::endl;
	// ======= RESIZE =======

	ft::vector<int> myvector(10, 3);

	// set some initial content:
	myvector.resize(0);
	std::cout << myvector[0] << std::endl;
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(8,100);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(12);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(12, 10);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	myvector.resize(100, 5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;
	//myvector.resize(SIZE_MAX, 5);
	std::cout << "capacity = " << myvector.capacity() << std::endl;
	std::cout << "size = " << myvector.size() << std::endl;

	ft::vector<int>::iterator	it = myvector.begin();
	ft::vector<int>::iterator	ite = myvector.end();

	std::cout << "myvector contains:";
	for ( ; it != ite ; it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "capacity = " << myvector.capacity() << std::endl;
}

int	main(void)
{
	test10();
}