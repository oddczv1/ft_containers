#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./iterator/util.hpp"
#include <vector>
#include <stack>
#include <map>

int main()
{
	//typedef std::map<std::string, int>::iterator iter;
    // std::map<std::string, int> n1;
	// n1.insert(std::make_pair("ac", 1));
	// n1.insert(std::make_pair("aa", 3));
	// n1.insert(std::make_pair("ab", 24));
	// n1.insert(std::make_pair("ab", 333));
	// std::cout << (n1["cc"] = 3) << std::endl;
	// std::cout << n1.max_size() << std::endl;
	// for(iter a = n1.begin(); a != n1.end(); a++)
    //     std::cout << "[" << a->first << ", " << a->second << "]" << " " << std::endl;

	
	// typedef ft::pair<std::string, int> pair;
	// pair a = ft::make_pair("a", 3);
	// pair b = ft::make_pair("b", 4);
	// pair c = ft::make_pair("c", 5);
	// pair d = ft::make_pair("d", 4);
	// pair bb = ft::make_pair("e", 4);
	// pair bb = ft::make_pair("f", 4);

	typedef ft::map<std::string, int>::iterator iter;
    ft::map<std::string, int> m1;
	m1.insert(ft::make_pair("b", 2));
	m1.insert(ft::make_pair("d", 4));	
	m1.insert(ft::make_pair("e", 5));
	m1.insert(ft::make_pair("a", 1));
	m1.insert(ft::make_pair("f", 6));
	m1.insert(ft::make_pair("c", 3));
	iter b = m1.end();
	std::cout << "[" << b->first << ", " << b->second << "]" << " " << std::endl;
	//std::cout << "aaaaa"<< std::endl;
	//m1.erase(b);
	//std::cout << "bbbbb"<< std::endl;
	//std::cout << m1["b"] << std::endl;
	//std::cout << "cccc"<< std::endl;
	for(iter a = m1.begin(); a != m1.end(); a++)
       std::cout << "[" << a->first << ", " << a->second << "]" << " " << std::endl;


	

    //std::cout << "지워져야함1 " <<  a->first << std::endl;

	//m1.erase(a);
	//std::cout << "지워져야함2 " <<  m1["a"] << std::endl;





	// const auto [it, success] = m1.insert(bb);
	// std::cout << it->first << "  " << it->second << "   " << success << std::endl;
	// std::cout << m1.at("aa") << std::endl;
	// std::cout << m1.at("bb") << std::endl;
	// std::cout << m1.at("cc") << std::endl;
	// std::cout << m1["aa"] << std::endl;
	// std::cout << m1["bb"] << std::endl;
	// std::cout << (m1["cc"] = 6) << std::endl;
	//const auto [it, success] = m1.insert(ft::pair<std::string, int>("me", 20));


	// for(iter a = m2.begin(); a != m2.end(); a++)
    //     std::cout << "[" << a->first << ", " << a->second << "]" << " " << std::endl;
	// std::cout << m1.max_size()<< std::endl;

	// typedef std::map<std::string, int>::iterator iter1;



	// n1.insert(std::pair<std::string, int>("me", 20));
	// n1.insert(std::pair<std::string, int>("me1", 13));
	// n1["lme"] = 3;
	// n1.at("lme") = 4;
	// std::map<std::string, int> n2(n1);
	// //std::cout << n2.count("me1") << std::endl;
	// for(iter1 a = n2.begin(); a != n2.end(); a++)
    //     std::cout << "[" << a->first << ", " << a->second << "]" << " " << std::endl;
	// std::cout << n1.max_size()<< std::endl;
	// std::cout << std::endl;
	/*

	std::map<std::string, int> m;
    std::map<std::string, int> m1(m.begin(), m.end());
	typedef std::map<std::string, int>::iterator iter;
	typedef std::pair<iter,bool> aa;
	aa bb = m1.insert(std::pair<std::string, int>("me", 20));
	if (!bb.second)
	{
    	bb.first->second = 30;
	}

 */
    // Overload 3: insert from rvalue reference



	/*
	m.insert(ft::pair<std::string, int>("me", 20));
	std::map<std::string, int>::iterator iter;
    
    for(iter = m.begin(); iter != m.end(); iter++)
	{
        std::cout << "[" << iter->first << ", " << iter->second << "]" << " " ;
    }
	std::cout << std::endl;*/
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