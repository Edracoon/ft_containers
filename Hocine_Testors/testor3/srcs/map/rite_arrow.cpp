#include "common.hpp"
#include <list>

#define T1 float
#define T2 foo<int>
typedef _pair<const T1, T2> T3;

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(2.5 - i, (i + 1) * 7));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::reverse_iterator it(mp.rbegin());
	TESTED_NAMESPACE::map<T1, T2>::const_reverse_iterator ite(mp.rbegin());
	printSize(mp);

	mp.print_tree();
	std::cout << "DEBUG 1 : rite_arrow" << std::endl;
	printPair(++ite);
	std::cout << "DEBUG 2 : rite_arrow" << std::endl;
	printPair(ite++);
	std::cout << "DEBUG 3 : rite_arrow" << std::endl;
	printPair(ite++);
	std::cout << "DEBUG 4 : rite_arrow" << std::endl;
	printPair(++ite);
	std::cout << "DEBUG 5 : rite_arrow" << std::endl;

	it->second.m();
	ite->second.m();

	printPair(++it);
	printPair(it++);
	printPair(it++);
	printPair(++it);

	printPair(--ite);
	printPair(ite--);
	printPair(--ite);
	printPair(ite--);

	(*it).second.m();
	(*ite).second.m();

	printPair(--it);
	printPair(it--);
	printPair(it--);
	printPair(--it);

	return (0);
}
