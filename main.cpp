#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./v_c.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>

#include <iostream>
#include <cstring>


#define TESTED_TYPE std::string



int main()
{

	// TESTED_NAMESPACE::vector<TESTED_TYPE> vct(10);
	// TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;

	
	// for (unsigned long int i = 0; i < vct.size(); ++i)
	// 	vct[i] = (vct.size() - i) * 3;
	// printSize(vct);

	// vct2.insert(vct2.end(), 42);
	// printSize(vct2);
	// vct2.insert(vct2.begin(), 2, 21);
	// printSize(vct2);

	// vct2.insert(vct2.end() - 2, 42);
	// printSize(vct2);

	// vct2.insert(vct2.end(), 2, 84);
	// printSize(vct2);

	// vct2.resize(4);
	// printSize(vct2);

	// vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	// vct.clear();
	// printSize(vct2);

	// printSize(vct);

	TESTED_NAMESPACE::vector<TESTED_TYPE> v1;

	v1.push_back("aaaa");

	TESTED_NAMESPACE::vector<TESTED_TYPE> v2;
	v2 = v1;

	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator iter1 = v1.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator iter2 = v2.begin();
	*iter1 = "bbbb";
	std::cout << iter2->c_str() << " && " << iter1->c_str() << std::endl;
	std::cout << &*iter2 << " && " << &*iter1 << std::endl;
	return (0);


}

// vector speed //
// #include <iostream>
// #include <chrono>
// #include <ctime>
// int main()
// {
//     auto start = std::chrono::system_clock::now();
//     std::vector<int> test;
//     for (int  i =0; i < 30000 ; i++){
//         test.push_back(i);
//     }
//     std::vector<int> test2;
//     test2 = test;
//     // Some computation here
//     auto end = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds = end-start;
//     std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//     std::cout << "finished computation at " << std::ctime(&end_time)
//               << "elapsed time: " << elapsed_seconds.count() << "s\n";
// }

// map seed //
// #include <iostream>
// #include <chrono>
// #include <ctime>
// int main()
// {
//     auto start = std::chrono::system_clock::now();
//     std::map<int, int> test;
//     for (int  i =0; i < 5000000 ; i++){
//         test.insert(std::make_pair(i, i));
//     }
//     for (int  i =0; i < 5000000 ; i++){
//         test.erase(i);
//     }
//     std::cout << "reach" << std::endl;
//     // Some computation here
//     auto end = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds = end-start;
//     std::time_t end_time = std::chrono::system_clock::to_time_t(end);
//     std::cout << "finished computation at " << std::ctime(&end_time)
//               << "elapsed time: " << elapsed_seconds.count() << "s\n";
// }

// vector leck check //
// #define ns ft
// struct A {
//     std::string* a;
//     A(std::string str);
//     A(const A& a);
//     A&  operator=(const A& a);
//     ~A();
// };
// A::A(std::string str) {
//     a = new std::string(str);
// }
// A::A(const A& a) {
//     this->a = new std::string(*a.a);
// }
// A& A::operator=(const A& a) {
//     delete this->a;
//     this->a = new std::string(*a.a);
//     return *this;
// }
// A::~A() {
//     delete a;
// }
// int main() {
//     {
//         std::string str = "asdfasdfsadfs";
//         ft::vector<A>  a = ft::vector<A>(4, A(str));
//         a.clear();
//     }
//     system("leaks test");
// }

