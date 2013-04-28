/*
 * interview.h
 *
 *  Created on: 2012-12-3
 *      Author: kevinguo
 */

#ifndef INTERVIEW_H_
#define INTERVIEW_H_
#include <vector>
#include <string>

/*
 * Problem1:
 * desc: �����ַ���A���ַ�����B,��A�в��Ұ���B�������ַ�������Ӵ�
 * solution: ��A�趨��ʼλ��,i=0,end=b_len,Ȼ�� end�������ɨ��,
 *       ��i->end����Ӵ�����Bʱ,�ڲ鿴i�Ƿ���Ҫ,����Ҫ(����B��Ҫ���ַ�,����i->end������ͬ�ַ�),��ʱi++
 */
bool IsIncludeByString(char a, char B[], int begin, int end);

bool IsAIncludeB(char A[], int begin, int end, char B[], int b_len);

int FindSubString(char A[], int a_len, char B[], int b_len);


/*
 * Problem2:�����ַ�����,��ӡ�ַ�ȫ����
 * @brief: Ŀǰ�����������Щ�ظ�.��3,2,1 �����8�����.
 */
void CalAllComb(char A[], int begin, int end, std::vector<std::string> &comb_result);

void PrintAllComb(char A[], int len);

/*
 * Problem3:����һ��int��,�����ö����Ʊ�ʾ�������,�ж��ٸ�1
 * ��:9�ö����Ʊ�ʾΪ1001,��2��1����
 * @brief:����һ�����λ,Ȼ�󲻶ϵ�����һλ,&������ж��ٸ�1
 */
int PrintBianryNum(int n);

/*
 * @brief:Ӧ��һ������, n & (n-1) �Ľ���ǰ�n �����ҵ�1��Ϊ0
 */
int PrintBianryNumEx(int n);


/*
 * Problem4: ��������Ľ׳�
 *
 * ���ݽṹ: |cnt|0~9|0~9|0~9|0~9|0~9|
 *             0   1   2   3   4  5
 */
int CalNBigNum(int n);

/*
 * Problem4: ��һ�������е������ŵ�ż��ǰ��
 */
bool IsOdd(int n);

int SortIntArray(int a[], int len, bool (*func)(int));


#endif /* INTERVIEW_H_ */
