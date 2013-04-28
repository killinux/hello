/*
 * graph.h
 *
 *  Created on: 2012-12-22
 *      Author: kevinguo
 *  @brief:图论相关的算法。
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include <iostream>
namespace graph
{
struct Node
{
public:
	Node():key(0),next(NULL) {}
	Node(int item): key(item),next(NULL) {}
	int key;
	Node *next;
	bool visited;
};

struct Head
{
public:
	Head(): key(0),list(NULL),tail(NULL),cnt(0),visited(false) {}
	int key;
	int DFS; //DFS树
	Node *list;
	Node *tail;
	int cnt;
	bool visited;
public:
	void AddItem(int item)
	{
		Node *node = new Node(item);
		if (cnt == 0) // first item
		{
			list = node;
			tail = node;
		}
		else
		{
			tail->next = node;
			tail = node;
		}
		cnt++;
	}
	void Print()
	{
		std::cout << "head.key=" << key << ",head.cnt=" << cnt << std::endl;
		Node *tmp = list;
		while (tmp != NULL)
		{
			std::cout << tmp->key << ",";
			tmp = tmp->next;
		}
	}
};

class Graph
{
public:
	void CreateGraph()
	{
		array = new Head[10];
		array[0].key = 1;
		array[0].AddItem(2);
		array[0].AddItem(6);
		array[0].AddItem(7);
		array[0].AddItem(10);

		array[1].key = 2;
		array[1].AddItem(3);
		array[1].AddItem(4);
		array[1].AddItem(6);

		array[2].key = 3;

		array[3].key = 4;
		array[3].AddItem(2);
		array[3].AddItem(6);
		array[3].AddItem(5);

		array[4].key = 5;
		array[4].AddItem(4);
		array[4].AddItem(6);

		array[5].key = 6;
		array[5].AddItem(5);
		array[5].AddItem(4);
		array[5].AddItem(2);
		array[5].AddItem(1);

		array[6].key = 7;
		array[6].AddItem(1);
		array[6].AddItem(10);
		array[6].AddItem(8);
		array[6].AddItem(9);

		array[7].key = 8;
		array[7].AddItem(9);
		array[7].AddItem(7);
		array[7].AddItem(10);

		array[8].key = 9;
		array[8].AddItem(8);
		array[8].AddItem(7);
		array[8].AddItem(10);

		array[9].key = 10;
		array[8].AddItem(8);
		array[8].AddItem(7);
		array[8].AddItem(1);
		array[8].AddItem(9);

	}
	void Print()
	{
		DepthFirstSearch(&array[0]);
	}
private:
	void DepthFirstSearch(Head *root)
	{
		root->visited = true;
		std::cout << preWork(root) << std::endl;

		Node *tmp = root->list;
		while (tmp != NULL)
		{
			if (!array[tmp->key - 1].visited)
				DepthFirstSearch(&array[tmp->key - 1]);
			tmp = tmp->next;
		}
	}
	int preWork(Head *head)
	{
		return head->key;
	}
private:
	Head *array;
};
}



#endif /* GRAPH_H_ */
