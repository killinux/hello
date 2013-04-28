/*
 * binary_search.h
 *
 *  Created on: 2012-11-14
 *      Author: kevinguo
 */

#ifndef BINARY_SEACH_H_
#define BINARY_SEACH_H_
#include <algorithm>
#include <vector>

/*
 * 二叉查找
 */
int BinarySearch(int a[], int len, int Key)
{
	int begin = 0;
	int end = len -1;

	while (end > begin)
	{
		int half = (begin+end)/2;
		if (a[half] == Key)
			return half;
		else if (a[half] > Key)
			end = half;
		else if (a[half] < Key)
			begin = half+1;
	}
	return 0;
}

// 环形队列, 求找其中最小元素
int CyclieBinarySearch(int a[], int len)
{
	int begin = 0;
	int end = len - 1;

	while (end > begin)
	{
		int half = (begin+end)/2;
		if (a[half] < a[end])
			end = half;
		else
			begin = half + 1;
	}
}

/**
 * <算法引论>P86;6.2.3,查找下标i,使得ai = i
 */
int SpecialBinarySearch(int a[], int len)
{
	int begin = 0;
	int end = len - 1;

	while (end > begin)
	{
		int half = (begin+end)/2;
		if (a[half] == half)
			return half;
		if (a[half] > half)
			end = half;
		else
			begin = half;
	}
    return 0;
}

/*
 * P89,内插搜索,适用于数据分布比较均匀的序列,
 *     平均比较次数为 O(log logN),但实际中体现不明显,1.n小的时候,log logN比logN体现不出来, 2.这种运算更复杂
 */
int InterPolationSearch(int a[], int len, int key)
{
	int left = 0;
	int right = len - 1;

	int guess_pos = (left + ((key - a[left])*(right - left)/(a[right] - a[left])));

	while (right > left)
	{
		if (a[guess_pos] ==  key)
		{
			cout << "find pos=" << guess_pos << endl;
			break;
		}
		else if (a[guess_pos] > key)
			right = guess_pos;
		else if (a[guess_pos] < key)
			left = guess_pos;

		guess_pos = (left + ((key - a[left])*(right - left)/(a[right] - a[left])));
	}

	return 0;
}

/*
 * Huffman_encoding,P105,
 */
class HuaffmanNode{
public:
	HuaffmanNode():c('0'),freq(0),left(NULL),right(NULL) {}
	char c;
	int freq;
	HuaffmanNode *left;
	HuaffmanNode *right;
};
bool CompareFunc(HuaffmanNode a, HuaffmanNode b)
{
	return (a.freq < b.freq);
}
// 中根递归遍历
void PrintFirstTree(HuaffmanNode *node) {
    if (node != NULL) {
    	printf("in Tree: %c\n", node->c);
    	PrintFirstTree(node->left);
    	PrintFirstTree(node->right);
    }
}
void HuffmanEncoding(HuaffmanNode a[], int len)
{
	vector<HuaffmanNode > my_heap(a,a+len);
    std::sort(my_heap.begin(),my_heap.end(), CompareFunc);

    while (!my_heap.empty())
    {
    	HuaffmanNode *first = new HuaffmanNode(my_heap.front());
    	my_heap.erase(my_heap.begin());
    	if (my_heap.empty()) //node为最后一个元素,作为树根
    	{
    		cout << "get root " << endl;
    		PrintFirstTree(first);
    		//cout << "head.freq=" << first.freq << ",head.c=" << first.c << endl;
    	}
    	else
    	{
    		HuaffmanNode *second = new HuaffmanNode(my_heap.front());
    		my_heap.erase(my_heap.begin());
    		HuaffmanNode *node = new HuaffmanNode();
    		node->freq = first->freq + second->freq;
    		node->left = first;
    		node->right = second;
    		my_heap.push_back(*node);
    		std::sort(my_heap.begin(),my_heap.end(), CompareFunc);
    	}
    }
}

#endif /* BINARY_SEACH_H_ */
