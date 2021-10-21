#include <iostream>
#include "../../../vector.hpp"

void	test1(void)
{
	std::cout << "==== ASSIGN ====" << std::endl;
	ft::vector<int>				vecti;

	vecti.push_back(32);
	vecti.push_back(634);
	vecti.push_back(12);
	
	vecti.assign(50, 100);
	vecti.assign(4, 10);

	ft::vector<int>::iterator	it = vecti.begin();
	ft::vector<int>::iterator	ite = vecti.end();
	for ( ; it != ite ; it++)
		std::cout << " " << *it << std::endl;
	std::cout << "size = " << vecti.size() << " capacity = " << vecti.capacity() << std::endl;
}

void test2( void )
{
	std::cout << "==== BEGIN_END ====" << std::endl;
	// =========================== 

	ft::vector<int>		vectint(10);

	std::cout << "capacity = " << vectint.capacity() << std::endl; 
	ft::vector<int>::iterator	it = vectint.begin();
	ft::vector<int>::iterator	it_cpy = it;
	ft::vector<int>::iterator	ite = vectint.end();
	while (it_cpy != ite)
	{
		std::cout << *it_cpy << " ";
		*it_cpy = 5;
		it_cpy++;
	}

	ft::vector<int>::iterator	it2 = vectint.begin();
	ft::vector<int>::iterator	ite2 = vectint.end();
	while (it2 != ite2)
	{
		std::cout << *it2 << " ";
		*it2 = 14;
		it2++;
	}

	std::cout << "size = " << vectint.size() << std::endl;
	ft::vector<int>::iterator	it3 = vectint.begin();
	ft::vector<int>::iterator	ite3 = vectint.end();
	while (it3 != ite3)
	{
		std::cout << *it3 << " ";
		*it3 = 14;
		it3++;
	}
}

void test3( void )
{
	std::cout << "==== CLEAR ====" << std::endl;
	ft::vector<int>	vectint;

	for (int i = 0 ; i < 10 ; i++)
		vectint.push_back(i);
	
	std::cout << "size before clear = " << vectint.size() << std::endl;

	std::cout << "is empty ? " << vectint.empty() << std::endl;

	vectint.clear();

	std::cout << "size after clear = " << vectint.size() << std::endl;

	vectint.clear();

	std::cout << "is empty ? " << vectint.empty() << std::endl;
}

void test4( void )
{
	std::cout << "==== FRONT_BACK_AT ====" << std::endl;
	ft::vector<int>				vecti;

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

	ft::vector<int>::iterator	it = vecti.begin();
	ft::vector<int>::iterator	ite = vecti.end();
	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl << "size = " << vecti.size() << " capacity = " << vecti.capacity() << std::endl;
}

void test5( void )
{
	std::cout << "==== INSERT_ASSIGN ====" << std::endl;
	ft::vector<int>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back(i);
	
	ft::vector<int>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;
	vectint.insert(it, 3, 800);

	ft::vector<int>				vectint_2;
	//vectint_2 = vectint;
	vectint_2.assign(vectint.begin(), vectint.end());
	std::cout << "vectint_2.capacity() = " << vectint_2.capacity() << " vectint_2.size() = " << vectint_2.size() << std::endl;

	ft::vector<int>::iterator	it2 = vectint_2.begin();
	for (int i = 0 ; i < 10 ; i++)
		it2++;

	vectint_2.insert(it2, vectint.begin(), vectint.end());
	
	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();
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

void test6( void )
{
	std::cout << "==== INSERT ====" << std::endl;
	ft::vector<int>				vectint;

	for ( int i = 0 ; i < 20 ; i++)
		vectint.push_back(i);

	ft::vector<int>::iterator	it = vectint.begin();

	for (int i = 0 ; i < 10 ; i++)
		it++;

	vectint.insert(it, 3, 800);

	std::cout << " vectint.capacity() = " << vectint.capacity() << " vectint.size() = " << vectint.size() << std::endl;

	ft::vector<int>				vectintcpy;

	vectintcpy = vectint;
	std::cout << "assignation vector" << std::endl;
	std::cout << " vectintcpy.capacity() = " << vectintcpy.capacity() << " vectintcpy.size() = " << vectintcpy.size() << std::endl;

	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();
	for ( ; it != ite ; it++ )
		std::cout << *it << " ";
	std::cout << std::endl;
}

void test7( void )
{
	std::cout << "==== OPERATOR= ====" << std::endl;
	ft::vector<int>				vecti;

	vecti.push_back(12);
	vecti.push_back(42);
	vecti.push_back(67);
	vecti.push_back(67);
	vecti.push_back(345);
	vecti.push_back(67);

	vecti.reserve(10);

	std::cout << std::endl << "vecti.size = " << vecti.size() << " vecti.capacity = " << vecti.capacity();
	
	ft::vector<int>				vecty;

	vecty = vecti;

	std::cout << std::endl;

	ft::vector<int>::iterator	it = vecty.begin();
	ft::vector<int>::iterator	ite = vecty.end();
	for ( ; it != ite ; it++)
		std::cout << *it << " ";
	std::cout << std::endl << "vecty.size = " << vecty.size() << " vecty.capacity = " << vecty.capacity();
	std::cout << std::endl << "vecti.size = " << vecti.size() << " vecti.capacity = " << vecti.capacity() << std::endl;
}

void test8( void )
{
	std::cout << "==== POP_BACK ====" << std::endl;
	// ==== POP_BACK ====
	ft::vector<int>	vectint;

	vectint.push_back(123);
	vectint.push_back(321);
	vectint.push_back(789);
	vectint.push_back(987);
	vectint.push_back(567);

	// vectint.resize(4);

	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	vectint.pop_back();
	std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	// vectint.pop_back();
	// std::cout << "capacity = " << vectint.capacity() << " size = " << vectint.size() << std::endl;
	// // un pop_back de trop -> size 0 - 1;

	// segfault car iteration sans limite
	ft::vector<int>::iterator	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();

	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

void test9( void )
{
	std::cout << "==== PUSH_BACK ====" << std::endl;
	// ==== PUSH_BACK ====
	ft::vector<int>	vectint;
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

	ft::vector<int>::iterator	it = vectint.begin();
	ft::vector<int>::iterator	ite = vectint.end();

	for ( ; it != ite ; it++)
		std::cout << " " << *it;
	std::cout << std::endl;
}

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

void	test12(void)
{
	ft::vector<int>		vectint;

	for (int i = 0 ; i < 20 ; i++)
		vectint.push_back(42);

	ft::vector<int>		range = ft::vector<int>(vectint.begin(), vectint.end());

	ft::vector<int>::iterator	it = range.begin();
	ft::vector<int>::iterator	ite = range.end();

	for ( ; it != ite ; it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "vectint.size = " << vectint.size() << " vectint.capacity() = " << vectint.capacity() << std::endl;
	std::cout << "range.size = " << range.size() << " range.capacity() = " << range.capacity() << std::endl;

	std::cout << "vectint.begin() = " << *(vectint.begin()) << std::endl;
	std::cout << "range.begin() = " << *(range.begin()) << std::endl;
}

int	main(void)
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
}