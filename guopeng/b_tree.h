/*
 * b_tree.h
 *
 *  Created on: 2011-11-10
 *      Author: shanshan
 */

#ifndef B_TREE_H_
#define B_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "circle_queue.h"

static const int B_LIMIT = 3;
static const int MAX_NUM_KEY = 2 * B_LIMIT - 1;
static const int SUB_NUM_KEY = B_LIMIT - 1; //���Ѻ��½ڵ�ĺ�����

struct B_Node {
    int num_key;
    char key[2*B_LIMIT - 1 + 1]; //key[0] no use
    bool leaf_flag;
    struct B_Node * child[2*B_LIMIT + 1]; //child[0] no use
};

struct Root {
	int num_node;
	 struct B_Node *first;
};

// ����һ���ڵ�
struct B_Node &AllocateNode() {
	struct B_Node *node = (struct B_Node *)malloc(sizeof(struct B_Node));
	node->num_key = 0;
	for (int i = 0; i <= MAX_NUM_KEY; i++) {
		node->key[i+1] = 'a';
	}
	node->leaf_flag = false;
	for (int i = 0; i < 2 * B_LIMIT; ++i) {
		node->child[i + 1] = NULL;
	}

	return *node;
}

void BTreeCreat(struct Root * &root) {
	struct B_Node &node = AllocateNode();
	node.leaf_flag = true;
	node.num_key = 0;
	root->first = &node;
}

void BTreeSplitChild(struct B_Node *parent, int pos, struct B_Node *child) {
	struct B_Node &new_child = AllocateNode();
	new_child.leaf_flag = child->leaf_flag;
	new_child.num_key = SUB_NUM_KEY;
	for (int j = 1; j <= SUB_NUM_KEY; j++) { //����keyֵ
		new_child.key[j] = child->key[j+B_LIMIT];
	}

	if (!child->leaf_flag) {
		for (int j = 1; j <= B_LIMIT; j++) { //��������
			new_child.child[j] = child->child[j+B_LIMIT];
		}
	}

	child->num_key = SUB_NUM_KEY;

	for (int j = parent->num_key + 1; j >= pos+1; j--) { //parent����һλ
		parent->child[j+1] = parent->child[j];
	}
	parent->child[pos+1] = &new_child;
	for (int j = parent->num_key; j >= pos; j--) {
		parent->key[j+1] = parent->key[j];
	}
	parent->key[pos] = child->key[B_LIMIT];
	parent->num_key += 1;

}

//
void BTreeInsertNonFull(struct B_Node *node, char k) {
	int pos = node->num_key;
	if (node->leaf_flag) {
		while (pos >= 1 && k < node->key[pos]) {
			node->key[pos+1] = node->key[pos];
			pos--;
		}
		node->key[pos+1] = k;
		node->num_key += 1;
	} else {
		while (pos >= 1 && k < node->key[pos]) {
			pos--;
		}
		pos += 1;
		if (node->child[pos]->num_key == MAX_NUM_KEY) {
			BTreeSplitChild(node, pos, node->child[pos]);
			if (k > node->key[pos]) {
				pos += 1;
			}
		}
		BTreeInsertNonFull(node->child[pos], k);
	}
}

void BTreeInsert(struct Root * root, char k) {
	struct B_Node *first = root->first;
	if (first->num_key == MAX_NUM_KEY) {
		struct B_Node &new_node = AllocateNode();
		new_node.leaf_flag = false;
		new_node.num_key = 0;
		new_node.child[1] = first;
		root->first = &new_node;

		BTreeSplitChild(&new_node, 1, first);
		BTreeInsertNonFull(&new_node, k);

	} else {
		BTreeInsertNonFull(first, k);
	}
}

struct B_Node *BTreeSearch(struct B_Node *node, char k, int &index) {
	int i = 1;
	while (i <= node->num_key && k > node->key[i]) {
		i += 1;
	}
	if (i <= node->num_key && k == node->key[i])
	{
		index = i;
		return node;
	}
	if (node->leaf_flag) {
		index = -1;
		return NULL;
	} else {
		return BTreeSearch(node->child[i], k, index);
	}
}
// ��֤k�����������ĸ�������Ϊt-1��
void BTreeDeleteNonSmall(struct B_Node *find_node, int find_index, char k) {
	if (find_node->leaf_flag) { //�����Ҷ�ӽڵ�,ֱ��ɾ��k
        for (int i = find_index; i < find_node->num_key; i++) {
			find_node->key[i] = find_node->key[i+1];
		}
		find_node->num_key--;
		return;
	}
	if (find_node->child[find_index]->num_key >= B_LIMIT) { //k��ǰ���ӽڵ�, P274-2a
		struct B_Node *pre_child = NULL;
		printf("in left \n");
		do {
			pre_child = find_node->child[find_index];
			find_node->key[find_index] = pre_child->key[pre_child->num_key];

			find_node = pre_child;
			find_index = find_node->num_key +1; //���Һ���
		} while (!pre_child->leaf_flag);
		pre_child->num_key--;
	} else if (find_node->child[find_index+1]->num_key >= B_LIMIT) { //k�ĺ���ӽڵ�, P274-2b
		struct B_Node *pos_child = NULL;
		printf("in right \n");
		do {
			pos_child = find_node->child[find_index+1];
			find_node->key[find_index] = pos_child->key[1];
			find_node = pos_child;
			find_index = 0; //������
		} while (!pos_child->leaf_flag);

		for (int i = 2; i <= pos_child->num_key; i++) {
			pos_child->key[i-1] = pos_child->key[i];
		}
		pos_child->num_key--;
	}

}

/****
 * �㷨���۵�18��
 * google����һ�µ������ǣ�
 *  ��һ���裺�����в��ұ�ɾ�ؼ���K���ڵĵص�
 *  �ڶ����裺����ɾȥK�Ĳ��� ��
 *  BTreeDelete������ѭ��������
 */
void BTreeDelete(struct Root * root, char k) {
	struct B_Node *find_node = NULL;
	int find_index;
	find_node = BTreeSearch(root->first, k, find_index);

	if (NULL != find_node) {
		if (find_node->leaf_flag) { //�����Ҷ�ӽڵ�,ֱ��ɾ��k
			for (int i = find_index; i < find_node->num_key; i++) {
				find_node->key[i] = find_node->key[i+1];
			}
			find_node->num_key--;
		} else {
			if ((find_node->child[find_index]->num_key >= B_LIMIT) || (find_node->child[find_index+1]->num_key >= B_LIMIT)) {
				BTreeDeleteNonSmall(find_node, find_index, k);
			} else { // �������ں��Ӹ�����ֻ��t-1�����ϲ�����p274-2c
				struct B_Node *pre_child = find_node->child[find_index];
				struct B_Node *pos_child = find_node->child[find_index+1];
				pre_child->num_key += 1;
				pre_child->key[pre_child->num_key] = k;// ����keyֵ
				int k_index = pre_child->num_key;
				for (int i = find_index; i < find_node->num_key; i++) {
					find_node->key[i] = find_node->key[i+1];
					find_node->child[i+1] = find_node->child[i+2];
				}
				find_node->num_key--;

				for (int i = 0; i < pos_child->num_key; i++) { // �ϲ��Һ���keyֵ��childֵ
					pre_child->num_key += 1;
					pre_child->key[pre_child->num_key] = pos_child->key[i+1];
					pre_child->child[pre_child->num_key] = pos_child->child[i+1];
				}

				delete pos_child;

				BTreeDeleteNonSmall(pre_child, k_index, k);
			}
		}
	} else {
		printf("not found %c", k);
	}


}

// �ֲ��ӡ, �����ڶ���
void BTreePrint(struct Root *root) {

	CircleQueue<B_Node> b_queue;
	b_queue.Init(100);

	struct B_Node *first = root->first;

    b_queue.Push(*first);

    printf("size = %d\n", b_queue.GetSize());

    int base_level = 0;
    struct B_Node *pop_node = (struct B_Node *)malloc(sizeof( struct B_Node));

    printf("\n------------level %d----------------\n", base_level);
    while (b_queue.GetSize() > 0) {

    	b_queue.Pop(*pop_node);
    	for (int i = 0; i < pop_node->num_key; i++) {
    		printf("%c, ", pop_node->key[i+1]);
    	}
    	printf("\n");

		if (!pop_node->leaf_flag) {
			base_level++;
			printf("\n------------level %d----------------\n", base_level);
			for (int i = 0; i < pop_node->num_key+1; i++) { // child����num_key��1
				b_queue.Push(*pop_node->child[i+1]);
			}
		}
    }

}

#endif /* B_TREE_H_ */
