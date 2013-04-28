/*
 * bit_sort.h
 *
 *  Created on: 2011-12-14
 *      Author: kevinguo
 */

#ifndef BIT_SORT_H_
#define BIT_SORT_H_

#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <set>

template <typename T>
void MakeData(std::list<T> &alist, int cnt, int max) {
	int need_data = 0;
	for (int i = 0; i < cnt; i++) {
        need_data = rand() % max;
        alist.push_back(need_data);
	}
}

bool ListCompare(int a, int b) {
	return (a < b);
}

/*****
 * 使用 bit 对集中的大数据量进行排序和存储. 一个unsigned char 可以有9bit的位置
 * @  见编程珠玑 P6
 */
template <typename T1>
void SortByBit(const std::list<T1> &alist, const int MAX_DATA_CNT) {
	if (alist.size() == 0) {
		return;
	}
	const int BYTE_LEN = MAX_DATA_CNT/8 + 1;
	unsigned char bit_char[BYTE_LEN];
	memset(bit_char, 0, BYTE_LEN);
	/**
	 * The rule of thumb is that if any part of the type you're using depends on a template,
	 * you need to use typename to convince the compiler that it really is a type
	 * error!!!!
	 * std::list<T1>::const_iterator con_iter = alist.begin();
	 */
	typename std::list<T1>::const_iterator con_iter;
	con_iter = alist.begin();
	while (con_iter != alist.end()) {
		int which_block = (*con_iter)/8; // 计算落在哪一个区间, 每个区间范围为0-7
		int which_position = (*con_iter)%8;
		bit_char[which_block] = (1<<which_position)|(bit_char[which_block]); // 根据which_position值对1进行移位
		con_iter++;
	}

	for (int block = 0; block < BYTE_LEN; block++) {
		for (int bit = 1, idx = 0; idx < 8; idx++, bit = (bit<<1)) {
			if (bit_char[block] & (bit & 0xFF)) {
				printf("%d, ", block*8 + idx);
			}
		}
	}

}

/***
 * 生成0 至 n-1 之间的 cnt个不同的随即顺序的随机整数
 * 有没有其他类似于集合的算法.!!!!!
 *
 * @2012-2-9
 * 可以采用集合方式, rand N 次, 随机调换两个key的位置, 最后取前cnt个key值
 */
template <typename T2>
bool GetRandKeySet(int cnt, int max, std::set<T2> &aset) {
	if (aset.size() != 0) {
		return false;
	}
	while (aset.size() < cnt) {
		int key = rand()%max;
		aset.insert(key);
	}
	return true;
}


#endif /* BIT_SORT_H_ */
