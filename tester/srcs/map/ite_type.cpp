#include "common.hpp"

int		main(void)
{
	TESTED_NAMESPACE::map<char, int>::iterator it;
	TESTED_NAMESPACE::map<char, int>::const_iterator ite;

	std::cout << (it != ite) << std::endl;
	std::cout << (it == ite) << std::endl;
	return (0);
}
