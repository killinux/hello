/*
 * binomial_heap.h
 *
 *  Created on: 2011-11-14
 *      Author: kevinguo
 */

#ifndef BINOMIAL_HEAP_H_
#define BINOMIAL_HEAP_H_

#include <stdio.h>
#include <stdlib.h>

struct HeapNode {
	struct HeapNode *parent;
	int key;
	int degree;
	struct HeapNode *child;
	struct HeapNode *sibling; //���ֵ�
};

struct Head {
	int num_heap;
	int num_node;
	struct HeapNode *first;
};

void PrintMergeLen(struct HeapNode *node);

// ������ͷ
void MakeHeapHead(struct Head * &head) {
	head = (struct Head *)malloc(sizeof(struct Head));
    assert(NULL != head);
	head->first = NULL;
	head->num_heap = 0;
	head->num_node = 0;

	return;
}

// ���ض�����СԪ��
struct HeapNode *HeapMinMum(struct Head *head) {
	struct HeapNode *min_node = NULL;
	struct HeapNode *x = head->first;
	int min_key = (1 << 30);
	while (NULL != x) {
		if (x->key < min_key) {
			min_key = x->key;
			min_node = x;
		} else {
			x = x->sibling;
		}
	}

	return min_node;
}
// �������ѽ��кϲ�
void HeapLink(struct HeapNode *son, struct HeapNode *par) {
    son->parent = par;
    son->sibling = par->child;
    par->child = son;
    par->degree += 1;
}

// ��h1��h2�ĸ���ϳ�һ�����������������������е�����
struct HeapNode *HeapMerge(struct Head *h1, struct Head *h2) {
    if (NULL == h1->first ) {
    	return h2->first;
    } else if (NULL == h2->first) {
    	return h1->first;
    }

    struct HeapNode *h1_curr_node = h1->first;
    struct HeapNode *h2_curr_node = h2->first;

    struct HeapNode *return_node = NULL;
    struct HeapNode *tail_node = NULL;

    if (h1_curr_node->degree <= h2_curr_node->degree) {
    	return_node = h1_curr_node;
    	h1_curr_node = h1_curr_node->sibling;
    } else {
    	return_node = h2_curr_node;
    	h2_curr_node = h2_curr_node->sibling;
    }
    tail_node = return_node;//��ʼ��ͷ���
    // tail_node->sibling = NULL;


    while (NULL != h1_curr_node && NULL != h2_curr_node) {
        if (h1_curr_node->degree <= h2_curr_node->degree) {
            tail_node->sibling = h1_curr_node;
            tail_node = h1_curr_node;
            h1_curr_node = h1_curr_node->sibling;
        } else {
        	tail_node->sibling = h2_curr_node;
        	tail_node = h2_curr_node;
        	h2_curr_node = h2_curr_node->sibling;
        }
    }

    if (NULL == h1_curr_node) {
    	tail_node->sibling = h2_curr_node;
    }
    if (NULL == h2_curr_node) {
    	tail_node->sibling = h1_curr_node;
    }

    return return_node;
}


struct Head * HeapUnion(struct Head *h1, struct Head *h2) {
	struct Head *new_head;
	MakeHeapHead(new_head);
	new_head->first = HeapMerge(h1, h2);
	PrintMergeLen(new_head->first);

	if (NULL == new_head->first) {
		return new_head;
	}
	struct HeapNode *prev_x = NULL;
	struct HeapNode *x = new_head->first;
	struct HeapNode *next_x = x->sibling;
	// ���㷨����P283-P284���ͣ��ǳ���ϸ
	while (NULL != next_x) {
        if ((x->degree != next_x->degree) || (next_x->sibling != NULL && x->degree == next_x->sibling->degree)) {
            prev_x = x;
            x = x->sibling;
        } else if (x->key <= next_x->key) {
        	x->sibling = next_x->sibling;
        	HeapLink(next_x, x);
        } else {
        	if (NULL == prev_x) {
        		new_head->first = next_x;
        	} else {
        		prev_x->sibling = next_x;
        	}
        	HeapLink(x, next_x);
        	x = next_x;
        }
        next_x = x->sibling;
	}

	// printf("in struct Head * HeapUnion, key=%d\n", new_head->first->key);
	return new_head;
}

// ����һ���ڵ�
// @brief h�ڵ�������, ��ΪҪ���޸���ָ��
void HeapInsertNode(struct Head *&h, struct HeapNode *node) {
	struct Head *new_head;
	MakeHeapHead(new_head);
	node->parent = NULL;
	node->degree = 0;
	node->sibling = NULL;
	node->child = NULL;
	new_head->first = node;
	assert(NULL != new_head->first);

	h = HeapUnion(h, new_head);
}

void HeapInsertKey(struct Head *&h, int key) {
	struct HeapNode *insert_node = (struct HeapNode *)malloc(sizeof(struct HeapNode));
	insert_node->key = key;
	HeapInsertNode(h, insert_node);
}



// 1. reverse h
// 2. set p field of each child to NULL
void HeapReverse(struct Head *h) {
    if (h->first == NULL) {
    	return;
    }
    struct HeapNode *first_node = h->first;
    h->first = NULL;
    struct HeapNode *need_deal = NULL;
    while (NULL != first_node) {
        need_deal = first_node;
        first_node = first_node->sibling;

        need_deal->parent = NULL;
        need_deal->sibling = h->first;
        h->first = need_deal;
    }
}
// ɾ����Сkeyֵ�Ľڵ�
struct HeapNode * HeapDeleteMinNode(struct Head *&h) { // ע��:�˴�������
	if (NULL == h->first) {
		return NULL;
	}
    struct HeapNode *min_node = HeapMinMum(h);
    if (h->first == min_node) { //�����ͷ���
    	h->first = min_node->sibling; //�Ӹ�����ɾ����С��min_node
    } else {
    	struct HeapNode *pre_node = h->first;
    	while (pre_node->sibling != min_node) {
    		pre_node = pre_node->sibling;
    	}
    	printf("pre_node->key=%d\n", pre_node->key);
    	pre_node->sibling = min_node->sibling;
    }
    struct Head *sub_head;
    MakeHeapHead(sub_head);
    sub_head->first = min_node->child;

    HeapReverse(sub_head);//��ת
    // PrintMergeLen(sub_head->first);
    h = HeapUnion(h, sub_head);
    // PrintMergeLen(h->first);

    return min_node;

}

// �˴�ֻ�����˼�Сkeyֵʱ, �ýڵ�Ӧ��ð������
// ���������keyֵ, ��ýڵ�Ӧ���½�
void HeapDecreaseKey(struct Head *h, struct HeapNode *node, int k) {
	if (k > node->key) {
		printf("error, only deal new_key < key \n");
		return;
	}
	node->key = k;
	struct HeapNode * curr = node;
	struct HeapNode * parent = curr->parent;

	while (NULL != parent && k < parent->key) {
		int tmp = parent->key;
		parent->key = curr->key;
		curr->key = tmp;

        curr = parent;
        parent = curr->parent;
	}
}

void HeapDeleteNode(struct Head *&h, struct HeapNode *node) {
	int negative_num = (1<<31); //��������ֲ��
	HeapDecreaseKey(h, node, negative_num);
	HeapDeleteMinNode(h);

}

struct HeapNode * SearchOne(struct HeapNode *node, int k) {
	if (NULL == node || node->key > k) {
		return NULL;
	}
	if (node->key == k) {
		return node;
	}
	struct HeapNode *return_node;
	return_node = SearchOne(node->child, k);
	return_node = SearchOne(node->sibling, k);

	return NULL;
}

// ����ָ����keyֵ
struct HeapNode * HeapSearchKey(struct Head *h, int k) {
	struct HeapNode * head = h->first;
	while (NULL != head) {
		if (head->key > k) {
			head = head->sibling;
		} else if (head->key == k) {
			return head;
		} else {
			struct HeapNode *local_node = head->child;
			struct HeapNode *result_node = SearchOne(local_node, k);
			if (NULL == result_node) {
				head = head->sibling;
			} else {
				return result_node;
			}

		}
	}
	return NULL;
}

void PrintOne(struct HeapNode *node) {

	if (NULL == node) {
		return;
	}
	struct HeapNode *local_node = node;
	printf("key=%d&degree=%d\n", local_node->key, local_node->degree);
	PrintOne(local_node->child);
	PrintOne(local_node->sibling);
}

void HeapPrint(struct Head *h) {
	struct HeapNode *heap = h->first;
	struct HeapNode *print_node = NULL;
    while (NULL != heap) {
    	print_node = heap;
    	printf("------------PrintOne-----------\n");
    	printf("key=%d&degree=%d\n", print_node->key, print_node->degree);
    	PrintOne(print_node->child);// heap ��ָ��Ӧ��OnePrint�����б��ı�
    	heap = heap->sibling;
    }
}

// ��ӡ�����ϵĸ�����
void PrintMergeLen(struct HeapNode *node) {
	assert(node != NULL);
	int cnt = 1;
	while (node->sibling != NULL) {
		cnt += 1;
		printf("%d, ", node->key);
		node = node->sibling;
	}
	printf("%d heap cnt=%d\n", node->key, cnt);
}

#endif /* BINOMIAL_HEAP_H_ */
