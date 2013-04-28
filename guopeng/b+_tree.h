/*
 * b+_tree.h
 *
 *  Created on: 2011-12-5
 *      Author: kevinguo
 *
 *  @Brief: B+ �� ,�����
 */

#ifndef B__TREE_H_
#define B__TREE_H_

#include <stdio.h>
#include <stdlib.h>

static const int B_PLUS_LIMIT = 3;
static const int MAX_LEAF_KEY_NUM = 2 * B_PLUS_LIMIT - 1;


struct InnerNode;

typedef struct LeafNode {
	int num_key; //��¼��ǰ�Ѱ������ٸ��ڵ�
	char key[MAX_LEAF_KEY_NUM + 1]; // key[0] no use
	struct LeafNode * brother_node;
	struct InnerNode *parent;
} SLeafNode;

typedef struct InnerNode {
	int num_key; //��¼��ǰ�Ѱ������ٸ��ڵ�
	SLeafNode * son_node_ptr[MAX_LEAF_KEY_NUM + 1];
	char son_node_min_key[MAX_LEAF_KEY_NUM + 1];
	struct InnerNode *parent;
} SInnerNode;

typedef struct BPlusRoot {
	SInnerNode * first;
}SRoot;

// ����Ҷ�ӽڵ�
SLeafNode & AllocateLeafNode() {
	SLeafNode *new_leaf = new SLeafNode;
	new_leaf->num_key = 0;
	for (int i = 0; i <= MAX_LEAF_KEY_NUM; i++) {
		new_leaf->key[i + 1] = 'a';
	}
	new_leaf->brother_node = NULL;
	new_leaf->parent = NULL;

	return *new_leaf;
}

// �����ڽڵ�
SInnerNode & AllocateInnerNode() {
	SInnerNode * new_inner = new SInnerNode();
	new_inner->num_key = 0;
	for (int i = 0; i <= MAX_LEAF_KEY_NUM; i++) {
		new_inner->son_node_ptr[i+1] = NULL;
	}
	for (int i = 0; i <=  MAX_LEAF_KEY_NUM; i++) {
		new_inner->son_node_min_key[i+1] = 'a';
	}
	new_inner->parent = NULL;
	return *new_inner;
}

void BPlusTreeCreate(SRoot * &root) {
	SInnerNode &first_node = AllocateInnerNode();
	first_node.num_key = 0;
	first_node.parent = NULL; //��һ���ڵ�parent Ϊ��
	root->first = &first_node;
}

// �����������ʱ, ��֤leaf��keyֵ����С��2t-1
void BPlusTreeInsertKeyIntoLeaf(SLeafNode *leaf, char k) {
	assert(leaf->num_key < MAX_LEAF_KEY_NUM);

	int pos = leaf->num_key;

	while (pos >= 0) {
		if (leaf->key[pos] > k) {
			leaf->key[pos+1] = leaf->key[pos];
			pos--;
		} else {
			leaf->key[pos+1] = k;
			break;
		}
	}
	leaf->num_key += 1;

}

/**
 * ������2t-1 ����ֵ��leaf�ڵ���ѳ� t �� t-1 .
 */
SLeafNode & BPlusTreeSplitLeaf(SLeafNode * big_leaf) {

	assert(big_leaf->num_key == MAX_LEAF_KEY_NUM);// ��ʱbig_leaf->num_key == MAX_LEAF_KEY_NUM

	SLeafNode & new_leaf = AllocateLeafNode();
	int pos = big_leaf->num_key;

	for (; pos > B_PLUS_LIMIT; pos--) {
		new_leaf.key[pos - B_PLUS_LIMIT] = big_leaf->key[pos];
		new_leaf.num_key += 1;
		big_leaf->num_key -= 1;
	}
	return new_leaf;
}

void BPlusTreeNotFullInsert(SInnerNode * inner_node, char k) {
	if (inner_node->num_key == 0) { // �ڽڵ������û��leaf
		SLeafNode & new_leaf = AllocateLeafNode();
		inner_node->son_node_ptr[1] = &new_leaf;
		inner_node->son_node_min_key[1] = k;
		inner_node->num_key = 1;
		new_leaf.parent = inner_node;

		BPlusTreeInsertKeyIntoLeaf(&new_leaf, k);
	} else {
		int leaf_idx = inner_node->num_key;

		while ((k < inner_node->son_node_min_key[leaf_idx]) && (leaf_idx > 1)) { //Ѱ�Һ��ʵ���Ҷ��
			leaf_idx -= 1;
		}
		SLeafNode * find_leaf = inner_node->son_node_ptr[leaf_idx];

		if (find_leaf->num_key == MAX_LEAF_KEY_NUM) { // leaf ����
			SLeafNode & new_leaf = BPlusTreeSplitLeaf(find_leaf);

			new_leaf.parent = find_leaf->parent;
			inner_node->num_key += 1;

			// printf("%d, %d\n", inner_node->num_key, new_leaf.num_key);

			// ������leaf�ڵ�������leaf�ڵ����һλ
			int pos = inner_node->num_key;
			for (; pos > leaf_idx+1; pos--) {
				inner_node->son_node_ptr[pos] = inner_node->son_node_ptr[pos-1];
				inner_node->son_node_min_key[pos] = inner_node->son_node_min_key[pos-1];
			}
			inner_node->son_node_ptr[pos] = &new_leaf;
			inner_node->son_node_min_key[pos] = new_leaf.key[1];

			if (inner_node->son_node_min_key[pos] < k) { //���¼��Ӧ�ò����ĸ�leaf�ڵ�
				find_leaf = inner_node->son_node_ptr[pos];
			} else {
                ; // ά�ַ���ǰ��leaf
			}

			BPlusTreeInsertKeyIntoLeaf(find_leaf, k);
		} else {
			BPlusTreeInsertKeyIntoLeaf(find_leaf, k);
		}
	}
    // printf("in BPlusTreeNotFullInsert(SInnerNode * inner_node, char k)\n");
}

void BPlusTreeInsert(SRoot * root, char k) {
	SInnerNode * first_inner = root->first;
	if (first_inner->num_key == MAX_LEAF_KEY_NUM) {
		printf("first_inner->num_key == MAX_LEAF_KEY_NUM\n");
	} else {
		BPlusTreeNotFullInsert(first_inner, k);
	}
}

void BPlusTreePrint(SRoot * root) {
	SInnerNode * first_inner = root->first;
	for (int n = 1; n <= first_inner->num_key; n++) {
	SLeafNode * leaf = first_inner->son_node_ptr[n];

	if (NULL != leaf) {
		for (int i = 1; i <= leaf->num_key; i++)
		    printf("first key = %c\n", leaf->key[i]);
	}
	printf("\n--------\n");
	}
}

#endif /* B__TREE_H_ */
