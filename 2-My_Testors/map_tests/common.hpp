

template<class map>
void	printSizeContent(map mp)
{
	std::cout << "=========- printSizeContent -==========" << std::endl << std::endl;
	std::cout << "map_test.size() = " << mp.size() << std::endl;
	std::cout << "map.empty() = " << mp.empty() << std::endl;

	typename map::iterator	it = mp.begin();
	typename map::iterator	ite = mp.end();

	for ( int i = 0 ; it != ite ; ++it ) {
		std::cout << "it = [" << it->first << " - " << it->second << "]" << std::endl;
		if (i++ >= 10) {
			std::cout << "Size superior to 10, stopping here" << std::endl;
			std::cout << "=======================================" << std::endl << std::endl;
			return ;
		}
	}
	std::cout << "=======================================" << std::endl << std::endl;
	return ;
}
