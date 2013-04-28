/*
 * binary_search_tree.h
 *
 *  Created on: 2011-10-11
 *  Author: kevinguo
 *  @brief:
 *      binary_search_tree
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

struct Node_Tree {
	int key;
	struct Node_Tree *p;
	struct Node_Tree *left;
	struct Node_Tree *right;
};

//
struct Head_Tree {
	int num_node;
	struct Node_Tree *first;

};

// insert
void InsertTree(struct Head_Tree *head, int new_key) {
	struct Node_Tree * new_ptr = (struct Node_Tree *) malloc (sizeof(struct Node_Tree));
	new_ptr->left = NULL;
	new_ptr->right = NULL;
	new_ptr->p = NULL;
	new_ptr->key = new_key;

	head->num_node++;

	struct Node_Tree *x = head->first;
	struct Node_Tree *y = NULL;

	while (x != NULL) {
		y = x;
		if (new_ptr->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	new_ptr->p = y;
	if (NULL == y) { // 如果Tree is empty
		head->first = new_ptr;
	} else if (new_ptr->key < y->key) {
		y->left = new_ptr;
	} else {
		y->right = new_ptr;
	}
}

// 中根递归遍历
void PrintMiddleTree(Node_Tree *node) {
    if (node != NULL) {
    	PrintMiddleTree(node->left);
        printf("in Tree: %d\n", node->key);
        PrintMiddleTree(node->right);
    }
}

// @brief 查找指定key值
// @return a point that point to key_node
struct Node_Tree * SearchTree(struct Head_Tree *head, int find_key) {
	Node_Tree *node = head->first;

	while (node != NULL && node->key != find_key) {
		if (find_key < node->key)
			node = node->left;
		else
			node = node->right;
	}

	return node;
}

// @brief 查找最小元素, 及树的最左节点
struct Node_Tree *FindMinTree(struct Node_Tree *node) {
	while (node->left != NULL) {
		node = node->left;
	}

	return node;
}

// @brief 查找最大元素, 及树的最右节点
struct Node_Tree *FindMaxTree(struct Node_Tree *node) {
	while (node->right != NULL) {
		node = node->right;
	}

	return node;
}

// @brief 返回key值的后继节点
struct Node_Tree *GetNextTree(struct Node_Tree *node) {
	if (NULL == node)
		return node;
	if (node->right != NULL) { // ①如果有右节点,直接返回右子树的最左节点
		return FindMinTree(node->right);
	}
	Node_Tree *y = node->p;
	// 返回上层父节点, 直至node在左分支
	while (NULL != y && node == y->right) {
		node = y;
		y = y->p;
	}

	return y;
}

// @brief 返回key值的前驱节点
struct Node_Tree *GetPreTree(struct Node_Tree *node) {
	if (NULL == node)
		return node;
	if (node->left != NULL) {
		return FindMaxTree(node->left);
	}

	Node_Tree *y = node->p;
	while (NULL != y && node == y->left) {
		node = y;
		y = y->p;
	}

	return y;
}

// @brief 删除节点
struct Node_Tree *DeleteTree(struct Head_Tree *head, struct Node_Tree *node) {
	struct Node_Tree *y;
	if (node->left == NULL || node->right == NULL) {
        y = node;// node 只有一个或者没有子节点, y直接指向node
	} else {
		y = GetNextTree(node); //node有两个节点,y指向z的后继
	}

	struct Node_Tree *x;
	if (y->left != NULL) {
		x = y->left;
	} else {
		x = y->right;
	}
    // tag1
	if (x != NULL)
		x->p = y->p;
	if (y->p == NULL) {
		head->first = x;
	} else if (y == y->p->left) {
		y->p->left = x;
	} else {
		y->p->right = x;
	}
	// tag2: 从tag1到tag2, 修改指针,删除节点y

	if (y != node) { // node有两个节点的情况, 复制y的内容到node, 即相当与删除node
		node->key = y->key;
	}

	return y;
}

#endif /* BINARY_SEARCH_TREE_H_ */
