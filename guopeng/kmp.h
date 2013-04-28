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
		if (j == 0 || p[i] == p[j]) { //相等，直接next+1
			i++;
			j++;
			next[i] = j;
		} else {
			j = next[j]; //不等，取j的next[j]，再进行比较
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
		// j=0，表示j的第一个元素匹配失败，取next【1】=0，用j的第一个元素和i的下一个元素进行比较
		if ( j == 0 || source[i] == patt[j]) { //匹配成功，i，j同时后移
			i++;
			j++;
		} else {
			j = next[j]; //匹配失败，i不变，j回溯
		}
	}

	if (j > patt_len)
		return (i - patt_len);
	else
		return 0;
}

#endif /* KMP_H_ */

