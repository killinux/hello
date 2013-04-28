//============================================================================
// Name        : sizeof.cpp
// Author      : kevin
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pure.h"
#include "binary_search_tree.h"
#include "dynamic_pro.h"
#include "b_tree.h"
#include "b+_tree.h"
#include "circle_queue.h"
#include "binomial_heap.h"
#include "dynamic_gold.h"
#include "01PackProblem.h"
#include "binary_search.h"
#include "graph.h"
#include "kinds_sort.h"
#include "max_subsequence.h"
using namespace std;

void  Print() {
	printf("hello in Print()\n");
}


int main()
{

#if 0
    // 测试纯虚class
	CollegeFrind obj;

	cout << obj.getName() << endl;

	// 测试多重继承
	bear *ptr = new panda(1000, 101);
	ptr->Print();

	panda ning(10001, 101);
	ning.danger::Print(1);
	panda ying = *(static_cast<panda *> (ptr));
	ying.localFunc();
#endif
#if 0
	// 测试函数指针
	void (*pf)() = Print;
	pf();
#endif


#if 0
	// 测试二叉树
	int tree_list[] = {15, 6, 8, 3, 7, 17, 20, 2, 4, 13, 9};
	Head_Tree *head = (Head_Tree *)malloc(sizeof(Head_Tree));
	head->num_node = 0;
	head->first = NULL;

	for (size_t i = 0; i < sizeof(tree_list)/sizeof(int); ++i) {
        InsertTree(head, tree_list[i]);
	}
	cout << "cnt=" << head->num_node << endl;
	PrintMiddleTree(head->first);

	struct Node_Tree *locate = SearchTree(head, 13);
	if (NULL != locate)
	    cout << "find key: " << locate->key << endl;

	cout << "mix key: " << FindMinTree(head->first)->key << endl;
	cout << "max key: " << FindMaxTree(head->first)->key << endl;

	cout << "next key: " << GetNextTree(locate)->key << endl;
	cout << "pre key: " << GetPreTree(locate)->key << endl;

	DeleteTree(head, locate);
	PrintMiddleTree(head->first);
#endif

#if 0
	// 动态规划
	FastWay();
#endif

#if 0
	// B树
	struct Root *root;
	BTreeCreat(root);
    BTreeInsert(root, 'G');
	BTreeInsert(root, 'X');
	BTreeInsert(root, 'P');
	BTreeInsert(root, 'M');
	BTreeInsert(root, 'A');
	BTreeInsert(root, 'B');
	BTreeInsert(root, 'Q');
	BTreeInsert(root, 'S');
	BTreeInsert(root, 'U');
	BTreeInsert(root, 'T');
	BTreeInsert(root, 'Z');

	BTreePrint(root);
	BTreeDelete(root, 'M');

	cout << "hello world" << endl;
	BTreePrint(root);
#endif

#if 0
	// 二项堆(有点复杂)
	struct Head *heap_head;
	MakeHeapHead(heap_head);
	for (int i = 1; i <= 10 ; i++) {
		HeapInsertKey(heap_head, i);
	}

	PrintMergeLen(heap_head->first);
	HeapPrint(heap_head);

	struct HeapNode *min_node = HeapDeleteMinNode(heap_head);
	printf("delete min_node->key=%d\n", min_node->key);
	HeapPrint(heap_head);

	struct HeapNode *find_node = HeapSearchKey(heap_head, 5);
	HeapPrint(heap_head);
	printf("find min_node->key=%d\n", find_node->key);
	// HeapDecreaseKey(heap_head, find_node, 1);
	HeapPrint(heap_head);
	HeapDeleteNode(heap_head, find_node);
	HeapPrint(heap_head);
#endif

#if 0
	B+树
	SRoot *root = new SRoot();
	BPlusTreeCreate(root);
	BPlusTreeInsert(root, 'g');
	BPlusTreeInsert(root, 'c');
	BPlusTreeInsert(root, 'm');
	BPlusTreeInsert(root, 't');
	BPlusTreeInsert(root, 'b');
	BPlusTreeInsert(root, 'd');
	BPlusTreePrint(root);
#endif

#if 0
	动态规划
	GetMaxGold mine(100, 5);
	cout << "max=" << mine.GetMaxValue(100,4) << endl;
	GetMaxRice rice(3, 3);
	cout << "max_rice=" << rice.GetMaxValue(2,2) << endl;
#endif

#if 0
    // 01 背包问题,详见<算法引论>P79
	int a[]= {0,2,3,5,6}; // 0为补位
	GetMaxPack(a, sizeof(a)/sizeof(int)-1, 16);
	//case1
	//GetPackExtra(a, sizeof(a)/sizeof(int)-1, 4);
	//case2
	//GetPackExtra(a, sizeof(a)/sizeof(int)-1, 37);
#endif

#if 0
	汉诺塔
	int honoi[] = {1,2,3};
	// HanoiTower(honoi, 3, 'a', 'b', 'c');
	HanoiTowerLoop(honoi, 3, 'a', 'b', 'c');

	vector<int> A(1,3);
	vector<int> B(1,2);
	vector<int> C(1,1);
	int a_len = A.size();
	int b_len = B.size();
	int c_len = C.size();
 	HanoiTowerExtra(A, a_len, B, b_len, C, c_len, 'A', 'B', 'C');
#endif

#if 0
 	二分查找
 	int a[] = {1,2,6,8,33,754,777};
 	int key = 755;
 	cout << "index=" << BinarySearch(a, sizeof(a)/sizeof(int), key) << endl;

 	int b[] = {3,1,8,10,13,15,19};
 	cout << "min_index=" << CyclieBinarySearch(b, sizeof(b)/sizeof(int)) << endl;

 	int c[] = {-1,1,8,10,13,64,44};
 	cout << "equal_index=" << SpecialBinarySearch(c, sizeof(c)/sizeof(int)) << endl;


 	int d[100];
 	for (int i = 0; i < 100; i++)
 		d[i] = i+1;
 	InterPolationSearch(d, sizeof(d)/sizeof(int), 3);

 	int e[] = {6,2,8,5,10,9,12,1,15,7,3}; //0为补位
 	FindMinK(e, sizeof(e)/sizeof(int), 3);

 	// huffman
 	HuaffmanNode node[6];
 	node[0].c = 'A';
 	node[0].freq = 5;
 	node[1].c = 'B';
 	node[1].freq = 2;
 	node[2].c = 'C';
 	node[2].freq = 3;
 	node[3].c = 'D';
 	node[3].freq = 4;
 	node[4].c = 'E';
 	node[4].freq = 10;
 	node[5].c = 'F';
 	node[5].freq = 1;
 	HuffmanEncoding(node, sizeof(node)/sizeof(HuaffmanNode));
#endif


#if 0
 	排序
 	int e[] = {53,24342,1212,6745,23,1,756,5867,33425,53634,243,9867,78976,98,88,45,21345,86798};
 	RadixSort(e, sizeof(e)/sizeof(int),5);
 	MergeSort(e, sizeof(e)/sizeof(int));
 	QuickSort(e, sizeof(e)/sizeof(int));

 	int a[] = {0,6,2,8,5,10,9,12,1,15,7,3,13,4,11,16,14}; //0为补位
 	HeapSort(a, sizeof(a)/sizeof(int)-1);
#endif

    char A[] = "xyxxyxyxyyyxyxyxyyxyxyxx";
    char B[] = "xyxyyxyxyxx";
    SearchString(A, sizeof(A)-1, B, sizeof(B)-1);

#if 0
            图的深度优先遍历

    graph::Graph graph;
    graph.CreateGraph();
    graph.Print();
#endif



 	cout << "hello world" << endl;

}
