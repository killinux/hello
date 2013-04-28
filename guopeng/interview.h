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
 * desc: 给定字符串A和字符集合B,在A中查找包含B中所有字符的最短子串
 * solution: 在A设定初始位置,i=0,end=b_len,然后 end不断向后扫描,
 *       当i->end间的子串包含B时,在查看i是否需要,不需要(不是B需要的字符,或者i->end间有相同字符),此时i++
 */
bool IsIncludeByString(char a, char B[], int begin, int end);

bool IsAIncludeB(char A[], int begin, int end, char B[], int b_len);

int FindSubString(char A[], int a_len, char B[], int b_len);


/*
 * Problem2:给定字符集合,打印字符全排列
 * @brief: 目前结果集还是有些重复.如3,2,1 会给出8中组合.
 */
void CalAllComb(char A[], int begin, int end, std::vector<std::string> &comb_result);

void PrintAllComb(char A[], int len);

/*
 * Problem3:给定一个int型,计算用二进制表示的情况下,有多少个1
 * 如:9用二进制表示为1001,由2个1构成
 * @brief:设置一个标记位,然后不断的左移一位,&后计算有多少个1
 */
int PrintBianryNum(int n);

/*
 * @brief:应用一个定理, n & (n-1) 的结果是把n 的最右的1变为0
 */
int PrintBianryNumEx(int n);


/*
 * Problem4: 计算大数的阶乘
 *
 * 数据结构: |cnt|0~9|0~9|0~9|0~9|0~9|
 *             0   1   2   3   4  5
 */
int CalNBigNum(int n);

/*
 * Problem4: 把一个数列中的奇数排到偶数前面
 */
bool IsOdd(int n);

int SortIntArray(int a[], int len, bool (*func)(int));


#endif /* INTERVIEW_H_ */
