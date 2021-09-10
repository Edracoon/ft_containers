#include <iostream>
#include <vector>

int	main( void )
{
	std::vector<int>			vectint;
	std::vector<float>			vectfloat;
	std::vector<std::string>	vectstring;
	
	std::cout << "vectint.capacity() : " << vectint.capacity() << std::endl;
	std::cout << "vectint.capacity() : " << vectfloat.capacity() << std::endl;
	std::cout << "vectint.capacity() : " << vectstring.capacity() << std::endl;

	std::vector<int>::const_iterator	it = vectint.begin();
	std::vector<int>::const_iterator	ite =  vectint.end();

	std::cout << (it == ite) << std::endl;
}
