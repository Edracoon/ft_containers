

template<class set>
void	printSizeContent(set st)
{
	std::cout << "=========- printSizeContent -==========" << std::endl << std::endl;
	std::cout << "set_test.size() = " << st.size() << std::endl;
	std::cout << "set.empty() = " << st.empty() << std::endl;

	typename set::iterator	it = st.begin();
	typename set::iterator	ite = st.end();

	for ( int i = 0 ; it != ite ; ++it ) {
		std::cout << "it = [" << *it << "]" << std::endl;
		if (i++ >= 10) {
			std::cout << "Size superior to 10, stopping here" << std::endl;
			std::cout << "=======================================" << std::endl << std::endl;
			return ;
		}
	}
	std::cout << "=======================================" << std::endl << std::endl;
	return ;
}
