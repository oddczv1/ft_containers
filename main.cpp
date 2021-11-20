//#include "./containers/vector.hpp"
//#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./iterator/util.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>

#define T1 int
#define T2 std::string

ft::map<T1, T2> mp;
ft::map<T1, T2>::iterator it = mp.end();


template <typename T>
std::string	printPair(const T &iterator, bool nl = true)
{
	std::cout << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		std::cout << std::endl;
	return ("");
}


void	ft_find(T1 const &k)
{
	ft::map<T1, T2>::iterator ret = mp.find(k);

	if (ret != it)
		printPair(ret);
	else
		std::cout << "map::find(" << k << ") returned end()" << std::endl;
}


void	ft_count(T1 const &k)
{
	std::cout << "map::count(" << k << ")\treturned [" << mp.count(k) << "]" << std::endl;
}

int main()
{
	mp[42] = "fgzgxfn";
	mp[25] = "funny";
	mp[80] = "hey";
	mp[12] = "no";
	mp[27] = "bee";
	mp[90] = "8";
	std::cout << mp.size() << std::endl;

	std::cout << "\t-- FIND --" << std::endl;
	ft_find(12);
	ft_find(3);
	ft_find(35);
	ft_find(90);
	ft_find(100);

	std::cout << "\t-- COUNT --" << std::endl;
	ft_count(-3);
	ft_count(12);
	ft_count(3);
	ft_count(35);
	ft_count(90);
	ft_count(100);

	mp.find(27)->second = "newly inserted mapped_value";
	std::cout << mp.size() << std::endl;

	ft::map<T1, T2>  c_map(mp.begin(), mp.end());
	std::cout << "const map.find(" << 42 << ")->second: [" << c_map.find(42)->second << "]" << std::endl;
	//std::cout << "const map.count(" << 80 << "): [" << c_map.count(80) << "]" << std::endl;
	// typedef std::map<std::string, int>::iterator iter1;
	// typedef std::map<std::string, int>::const_iterator iter2;

	// ft::map<std::string, int>::iterator iter;
	// ft::map<std::string, int>::const_iterator iter1;
	// std::cout << (iter == iter1) << std::endl;
	// std::cout << (iter != iter1) << std::endl;

	// std::map<int ,std::string>	map1;
	// map1["dddd"] = 2;
	// std::map<int ,std::string>	map2;
	// std::map<int ,std::string>::iterator it;
	// std::map<int ,std::string>::iterator it2;
	// std::pair<std::map<int ,std::string>::iterator, bool> ret;
	// map1.insert(std::make_pair(1, "one"));
	// ret = map2.insert(std::make_pair(4, "ssss"));

	// it = map1.insert(ret.first, std::make_pair(1, "two"));
	// std::cout << map1.begin()->first << ": " << map1.begin()->second << '\n';
	// std::cout << map1[1] << '\n';
	// std::cout << it->first << ": " << it->second << '\n';


}














/*
//vector
int main()
{
	typedef  ft::vector<int>::iterator iterator;
	typedef  std::vector<int>::iterator iterator1;
	std::vector<int> a1;
    ft::vector<int> a2;

	std::allocator<int> abc;
	std::vector<int> b1(abc);
    ft::vector<int> b2(abc);

	std::vector<int> c1(3, 2);
    ft::vector<int> c2(c1.begin(), c1.end());
	for (iterator i = c2.begin(); i != c2.end(); i++)
		std::cout <<"벡터"<<  *i << std::endl;
	std::cout << std::endl;

	std::vector<int> d1(3, 5);
	ft::vector<int> d2(6,6);

	ft::vector<int> e1(6, 7);
	ft::vector<int> e2(6,6);

	//std::cout << (e1 < e2) << std::endl;
	//std::cout << (e1 > e2) << std::endl;
	//std::cout << (e1 <= e2) << std::endl;
	//std::cout << (e1 >= e2) << std::endl;



	std::vector<int> e1(3, 6);
	e1.insert(e1.begin(), 1);
	std::vector<int> e3(7, 5);
	std::cout << &e3[0] << std::endl;
	e3 = e1;
	std::cout << &e3[0] << std::endl;
	//for (iterator1 i = e3.begin(); i != e3.end(); i++)
	//	std::cout << *i << std::endl;;

	// operator
	//std::cout << f1.front() << std::endl;
	//std::cout << f1.back() << std::endl;

	typedef  std::vector<int>::iterator aaa;
	aaa  bbb = f1.begin();
	for (int i = 0; i < 5; i++)
	{
		std::cout << *bbb << std::endl;
		bbb++;
	}

	//std::cout << &d1[0] << std::endl;
	//d1.reserve(4);
	//std::cout << &d1[0] << std::endl;

	std::vector<int> g1(5, 7);
	typedef  std::vector<int>::iterator aaa;
	//ccc += 0;
	//g1.insert(ccc, d1.begin(), d1.end());

	aaa begin = g1.begin();
	aaa end = g1.end();
	aaa return1 = g1.insert(begin, 5);

	for (aaa i = g1.begin(); i != g1.end(); i++)
		std::cout << *i;
	std::cout << std::endl;


	ft::vector<int> f1(3, 5);
	iterator abcd;
	abcd = f1.erase(f1.begin(),f1.begin());
    std::cout << &*abcd << std::endl;
    std::cout << "size"<< f1.size() << std::endl;
    std::cout << "capacity "<< f1.capacity() << std::endl;
	for (iterator i = f1.begin(); i != f1.end(); i++)
		std::cout <<"벡터"<<  *i << std::endl;
	std::cout << std::endl;

    ft::vector<int> numbers;
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
	for (iterator i = numbers.begin(); i != numbers.end(); i++)
		std::cout <<" 벡터:"<< *i;
	std::cout <<std::endl;

    numbers.pop_back();
	for (iterator i = numbers.begin(); i != numbers.end(); i++)
		std::cout <<" 벡터:"<< *i;
	std::cout <<std::endl;
    std::cout <<numbers[2] <<std::endl;


    ft::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
    ft::reverse_iterator<ft::vector<int>::iterator> iter = v.rbegin();
    for (std::size_t i{}; i != v.size(); ++i)
       std::cout << iter[i] << ' '; // the type of iter[i] is `int&`
    std::cout << '\n';

}



template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename ft::iterator_traits<BidirIt>::difference_type n = ft::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

int main()
{
    ft::vector<int> v;
	v.push_back(0);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
    my_reverse(v.begin(), v.end());
    for (int i = 0; i < 5; i++)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}
*/