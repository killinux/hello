/*
 * max_subsequence.h
 *
 *  Created on: 2012-11-11
 *      Author: Guopeng
 */

#ifndef MAX_SUBSEQUENCE_H_
#define MAX_SUBSEQUENCE_H_

#include <stdio.h>

using namespace std;

/**
 * @brief:����һ�����飨���������͸��������������������������
 * @input:���飬���鳤��
 * @output����������к�
 * @more:�ο����㷨���ۡ�76ҳ
 */
int GetMaxSubSequence(int a[], size_t len)
{
	int global_max = 0;
	int suffix_max = 0;//��׺�����������
	int begin = 0;
	int end = 0;
	int max_begin,max_end = 0;

	for (size_t i = 0; i < len; i++)
	{
		if ((a[i] + suffix_max) > global_max)
		{
			suffix_max = a[i] + suffix_max;
			global_max = suffix_max;
			end = i;
			max_begin = begin;
			max_end = end;
		}
		else if ((a[i] + suffix_max) > 0)
		{
			suffix_max = a[i] + suffix_max;
			end = i;
		}
		else
		{
			suffix_max = 0;
			begin = i;
		}
	}
	cout << "i=" << max_begin << ",j=" << max_end << endl;
	return global_max;
}


/*
 * Ѱ�������ַ���������Ӵ�, ����������kmp�㷨
 * next ���±��1��ʼ.
 */
void  ComputeNext(char b[], int len, int *next)
{
	next[0] = -1;
	for (int i = 0; i < len; i++)
	{
		next[i+1] = next[i] + 1;
		while ((next[i+1] > 0) && (b[i] != b[next[i+1] -1]))
			next[i+1] = next[next[i+1]-1] + 1;
    }
}

/**
 * KMP �㷨
 */
void SearchString(char A[], int a_len, char B[], int b_len)
{
	int next[b_len];
	ComputeNext(B, b_len, next);
	for (int i = 0; i < b_len; i++)
		std::cout << "next[" << i << "]=" << next[i] << std::endl;

	int i = 0;
	int j = 0;
	int start = 0;
	while((start == 0) && (i < a_len))
	{
		if (A[i] == B[j])
		{
			i++;
			j++;
		}
		else
		{
			if (j == 0)
				i++;
			else
			    j = next[j];

		}
		if (j == b_len-1)
			start = i - b_len;
	}
	std::cout << "start=" << start <<"," << A[start] << std::endl;
	std::cout << "sub_string=" << A + start + 1 << std::endl;
}

#endif /* MAX_SUBSEQUENCE_H_ */
