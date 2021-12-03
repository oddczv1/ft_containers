#include "./containers/vector.hpp"
#include "./containers/stack.hpp"
#include "./containers/map.hpp"
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <iostream>
#include <chrono>
#include <ctime>

// test vector 헤더 //
#include "./tester/for_test_vector.hpp"

// test map 헤더 //
//#include "./tester/for_test_map.hpp"

///////////////////////////////////////////////////////////////////////////////////////////

//// vector base ////

#define TESTED_TYPE int

int		main(void)
{
    typedef TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator iter;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct1(7);
    TESTED_NAMESPACE::vector<TESTED_TYPE> vct2(4);

	for (unsigned long int i = 0; i < vct1.size(); ++i)
		vct1.at(i) = (vct1.size() - i) * 3;
	for (unsigned long int i = 0; i < vct2.size(); ++i)
		vct2.at(i) = (vct2.size() - i) * 5;

    std::cout << "[vct1]" << std::endl;
	printSize(vct1);
    std::cout << "[vct2]" << std::endl;
    printSize(vct2);
    iter vct1_begin = vct1.begin();
    iter vct2_begin = vct2.begin();

    std::cout << "vct1 begin() : " << *vct1_begin << std::endl;
    std::cout << "vct2 begin() : " << *vct2_begin << std::endl;

    vct1.swap(vct2);
    std::cout << "\n\n*********after swap*********" << std::endl;
    std::cout << "[vct1]" << std::endl;
	printSize(vct1);
    std::cout << "[vct2]" << std::endl;
    printSize(vct2);
    std::cout << "vct2 begin() : " << *vct1_begin << std::endl;
    std::cout << "vct1 begin() : " << *vct2_begin << std::endl;

	return (0);
}

///////////////////////////////////////////////////////////////////////////////////////////

//// vector speed ////

// int max = 50000000;

// int main()
// {
// 	typedef std::chrono::system_clock::time_point time_clock;
//     time_clock start = std::chrono::system_clock::now();

//     TESTED_NAMESPACE::vector<int> test;
//     for (int  i =0; i < max ; i++){
//         test.push_back(i);
//     }
//     TESTED_NAMESPACE::vector<int> test2;
//     test2 = test;

//     time_clock end = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds = end-start;
//     std::cout << "*****[check time]*****\n[ft] elapsed time: " << elapsed_seconds.count() << "s\n";

// 	////////////////////////////////////////////////////////

//     time_clock start1 = std::chrono::system_clock::now();

//     std::vector<int> test3;
//     for (int  i =0; i < max ; i++){
//         test3.push_back(i);
//     }
//     std::vector<int> test4;
//     test4 = test3;

//     time_clock end1 = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds1 = end1-start1;
//     std::cout << "[std] elapsed time: " << elapsed_seconds1.count() << "s\n";
// 	std::cout << "speed: " << elapsed_seconds1.count() / elapsed_seconds.count() << " (std/ft)\n";

// }

///////////////////////////////////////////////////////////////////////////////////////////

//// vector leck check ////

// #define TESTED_TYPE foo

// int main() {
//     {
//         TESTED_NAMESPACE::vector<TESTED_TYPE>  a = TESTED_NAMESPACE::vector<TESTED_TYPE>(4, foo());
//         a.clear();
//     }
//     system("leaks test");
// }

///////////////////////////////////////////////////////////////////////////////////////////

//// map base ////
// #define T1 int
// #define T2 foo<float>

// typedef TESTED_NAMESPACE::map<T1, T2> _map;
// typedef _map::iterator iter;

// int		main(void)
// {
// 	_map	mp;

// 	mp[1] = 2.3;
// 	mp[3] = 1.4;
// 	mp[4] = 0.3;
// 	mp[7] = 4.2;
//     mp.insert(ft::make_pair(8, 1.1));
// 	//mp.treePrint_int();

//     printSize(mp);
//     std::cout << "[begin]" << std::endl;
//     std::cout << "- key: "<<mp.begin()->first << " | " << "value: "<< mp.begin()->second << std::endl;
//     std::cout << "\n\n\n*********after erase*********" << std::endl;
//     mp.erase(mp.begin());
//     printSize(mp);
//     std::cout << "[begin]" << std::endl;
//     std::cout << "- key: "<<mp.begin()->first << " | " << "value: "<< mp.begin()->second << std::endl;
//     std::cout << "\n\n\n*********after insert*********" << std::endl;
//     mp[2] = 2.2;
//     printSize(mp);
//     std::cout << "[begin]" << std::endl;
//     std::cout << "- key: "<<mp.begin()->first << " | " << "value: "<< mp.begin()->second << std::endl;
// 	return (0);
// }

///////////////////////////////////////////////////////////////////////////////////////////

//// map seed ////

// int main()
// {
// 	typedef std::chrono::system_clock::time_point time_clock;
// 	int max = 5000000;

// 	//ft//
//     time_clock start = std::chrono::system_clock::now();
// 	//////////////////////////
//     TESTED_NAMESPACE::map<int, int> test;
//     for (int  i =0; i < max ; i++){
//         test.insert(TESTED_NAMESPACE::make_pair(i, i));
//     }
//     for (int  i =0; i < max ; i++){
//         test.erase(i);
//     }
//     //////////////////////////
//     time_clock end = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds = end-start;
// 	std::cout << "*****[check time]*****\n[ft] elapsed time: " << elapsed_seconds.count() << "s\n";

// 	//std//
//     time_clock start1 = std::chrono::system_clock::now();
// 	//////////////////////////
//     std::map<int, int> test1;
//     for (int  i =0; i < max ; i++){
//         test1.insert(std::make_pair(i, i));
//     }
//     for (int  i =0; i < max ; i++){
//         test1.erase(i);
//     }
//     //////////////////////////
//     time_clock end1 = std::chrono::system_clock::now();
//     std::chrono::duration<double> elapsed_seconds1 = end1-start1;
//     std::cout << "[std] elapsed time: " << elapsed_seconds1.count() << "s\n";
// 	std::cout << "speed: " << elapsed_seconds1.count() / elapsed_seconds.count() << " (std/ft)\n";
// }

///////////////////////////////////////////////////////////////////////////////////////////

// // map leck check ////

// #define T1 char
// #define T2 foo<float>

// typedef _pair<const T1, T2> T3;

// int main() 
// { 
// 	std::list<T3> lst;
// 	unsigned int lst_size = 5;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(2.5 + i, i + 1));

// 	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
// 	lst.clear();
//     mp.clear();

//     system("leaks test");
// }
