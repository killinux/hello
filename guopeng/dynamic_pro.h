/*
 * dynamic_pro.h
 *
 *  Created on: 2011-10-17
 *      Author: kevinguo
 */

#ifndef DYNAMIC_PRO_H_
#define DYNAMIC_PRO_H_

#include <stdio.h>

// �μ�<�㷨����> p193
void FastWay() {
	//װ���Ĵ���ʱ��
	int a1[] = {0, 7, 9, 3, 4, 8, 4}; // 0Ϊռλ
	int a2[] = {0, 8, 5, 6, 4, 5, 7};

	int t1[] = {2, 2, 3, 1, 3, 4, 3};
	int t2[] = {4, 2, 1, 2, 2, 1, 2};

	int e1 = t1[0];//����װ����
	int e2 = t2[0];

	int len = sizeof(t1)/sizeof(int);

	int x1 = t1[len - 1];//��װ����
	int x2 = t2[len - 1];

	int f1[len];//��¼��ʱ
	int f2[len];

	int road1[len];//��¼·��
	int road2[len];

	f1[1] = e1 + a1[1];
	f2[2] = e2 + a2[1];

	for (int j = 2; j <= len; j++) {
		if ((f1[j-1] + a1[j]) <= (f2[j-1] + t2[j-1] + a1[j])) {
			f1[j] = (f1[j-1] + a1[j]);
			road1[j] = 1;
		} else {
			f1[j] = (f2[j-1] + t2[j-1] + a1[j]);
			road1[j] = 2;
		}
		if ((f2[j-1] + a2[j]) <= (f1[j-1] + t1[j-1] + a2[j])) {
			f2[j] = (f2[j-1] + a2[j]);
			road2[j] = 2;
		} else {
			f2[j] = (f1[j-1] + t1[j-1] + a2[j]);
			road2[j] = 1;
		}
	}

	int min = 0;
	if ((f1[len] + x1) <= (f2[len] + x2)) {
		min = f1[len] + x1;
	} else {
		min = f2[len] + x2;
	}

	printf("min_cost = %d\n", min);

	for (int i = 1; i <= len; i++) {
		printf("road = %d\n", road1[i]);
	}



}


#endif /* DYNAMIC_PRO_H_ */
