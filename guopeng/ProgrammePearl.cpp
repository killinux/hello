//============================================================================
// Name        : ProgrammePearl.cpp
// Author      : kevin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>
#include <set>
#include <algorithm>
#include "bit_sort.h"
#include "interview.h"

using namespace std;

static const int MAX_DATA_CNT = 999999;

int main() {

#if 0
	// sort list by bit
	list<int> data_list;
	MakeData<int>(data_list, 100, MAX_DATA_CNT);

	list<int> test_list(data_list);
	test_list.sort();
	list<int>::iterator iter = test_list.begin();
	while (iter != test_list.end()) {
		printf("%d, ", *iter);
		iter++;
	}
	printf("\nlist.size()=%d\n", test_list.size());

	SortByBit<int>(data_list, MAX_DATA_CNT);
#endif

#if 0
	// 在0--n-1之间随机生成K个数
	std::set<int> key_set;
	GetRandKeySet(99, 100000, key_set);
	std::set<int>::const_iterator con = key_set.begin();
	while (con != key_set.end()) {
		printf("%d, ", *con);
		con++;
	}
#endif

#if 0
	在字符串中查找包含某个字符集合的子串.
    char A[] = "abcdeabmccdfbcm";
    char B[] = {'b','c','d'};
    FindSubString(A, sizeof(A), B, sizeof(B));
#endif

#if 0
    打印元素的所有组合,重点在于子问题的复用,目前的算法,结果上有重复的情况
    char A[] = {'1','2','3'};
    PrintAllComb(A, sizeof(A));
#endif

#if 0
    移位
    PrintBianryNum(9);
    PrintBianryNumEx(9);
#endif

#if 0
    计算大数
    CalNBigNum(100);
#endif

    int a[5] = {1,2,3,4,5};
    SortIntArray(a, sizeof(a)/sizeof(int), IsOdd);

	cout << "Hello World!!!" << endl; // prints Hello World!!!
	return 0;
}
