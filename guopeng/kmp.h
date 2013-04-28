/*
 * kmp.h
 *
 *  Created on: 2011-10-8
 *      Author: shanshan
 */

#ifndef KMP_H_
#define KMP_H_

//
void getNext(char p[], int len, int next[]) {

	next[1] = 0;
	int i = 1;
	int j = 0;

	while ( i < len) {
		if (j == 0 || p[i] == p[j]) { //��ȣ�ֱ��next+1
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j]; //���ȣ�ȡj��next[j]���ٽ��бȽ�
		}
	}

}

int findIndexKMP(char source[], int source_len, char patt[], int patt_len) {

	int next[patt_len+1];
	getNext(patt, patt_len, next);
	for (int i = 1; i <= patt_len; i++) {
		printf("%d, ", next[i]);
	}
	int i = 1;
	int j = 1;

	while ( i <= source_len && j <= patt_len) {
		// j=0����ʾj�ĵ�һ��Ԫ��ƥ��ʧ�ܣ�ȡnext��1��=0����j�ĵ�һ��Ԫ�غ�i����һ��Ԫ�ؽ��бȽ�
		if ( j == 0 || source[i] == patt[j]) { //ƥ��ɹ���i��jͬʱ����
			i++;
			j++;
		} else {
			j = next[j]; //ƥ��ʧ�ܣ�i���䣬j����
		}
	}

	if (j > patt_len)
		return (i - patt_len);
	else
		return 0;
}

#endif /* KMP_H_ */

