#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./c_vector.hpp"
//#include "./c_map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>

#define TESTED_TYPE int

int		main(void)
{

	TESTED_NAMESPACE::vector<TESTED_TYPE> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	//TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator iter1 = v.begin();
	//TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator iter2 = v.end();

	std::cout << "### before assign(): ###" << std::endl;
	std::cout << v.capacity() << " " << v.size() << std::endl;
	std::cout << "#########################" << std::endl;
	v.resize(5);
	std::cout << "### After assign(): ###" << std::endl;
	std::cout << v.capacity() << " " << v.size() << std::endl;
	std::cout << "#########################" << std::endl;

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

