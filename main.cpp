#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include "./c_vector.hpp"
//#include "./c_map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>

#include <iostream>
#include <cstring>


#define TESTED_TYPE int

int		main(void)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(5);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

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

