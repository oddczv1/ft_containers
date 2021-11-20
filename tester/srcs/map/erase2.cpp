#include "common.hpp"
#include <list>

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "ret: " << mp.erase(param) << std::endl;
	printSize(mp);
}

int		main(void)
{
	TESTED_NAMESPACE::map<int, std::string>	mp1;
	mp1[1] = "11"; mp1[2] = "12"; mp1[3] = "13"; mp1[4] = "14";
	mp1[5] = "15"; mp1[6] = "16"; mp1[7] = "17"; mp1[8] = "18";
	mp1[9] = "19"; mp1[10] = "20";
	TESTED_NAMESPACE::map<T1, T2> mp(mp1.begin(), mp1.end());
	printSize(mp);

	for (int i = 2; i < 4; ++i)
		ft_erase(mp, i);

	ft_erase(mp, mp.begin()->first);
	ft_erase(mp, (--mp.end())->first);

	mp[-1] = "Hello";
	mp[10] = "Hi there";
	mp[10] = "Hi there";
	printSize(mp);

	ft_erase(mp, 0);
	ft_erase(mp, 1);

	return (0);
}
