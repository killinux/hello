#include <iostream>
#include "interview.h"

using namespace std;

/*
 * Problem1:
 * desc: 给定字符串A和字符集合B,在A中查找包含B中所有字符的最短子串
 * solution: 在A设定初始位置,i=0,end=b_len,然后 end不断向后扫描,
 *       当i->end间的子串包含B时,在查看i是否需要,不需要(不是B需要的字符,或者i->end间有相同字符),此时i++
 */
bool IsIncludeByString(char a, char B[], int begin, int end)
{
	for (int i = begin; i <= end; i++)
	{
		if (a == B[i])
			return true;
	}

	return false;
}


bool IsAIncludeB(char A[], int begin, int end, char B[], int b_len)
{

	//std::cout << "B=" << B << ",b_len=" << b_len << std::endl;
	for (int i = 0; i < b_len; i++)
	{
		//std::cout << "begin=" << begin << ",end=" << end << ",b=" << B[i] << std::endl;
		if(!IsIncludeByString(B[i], A, begin, end))
			return false;
	}
	return true;
}

int FindSubString(char A[], int a_len, char B[], int b_len)
{
	int sub_len = a_len;
	int min_start = 0;
	int min_end = a_len;
	int start = 0;
	for (int end = b_len - 1; end < a_len; end++)
	{
		if (IsAIncludeB(A, start, end, B, b_len))
		{
			while (end - start + 1 >= b_len)
			{
				if (!IsIncludeByString(A[start], B, 0, b_len-1))
					start++;
				else if (IsIncludeByString(A[start], A, start+1, end))
					start++;
				else
					break;
			}
			if (end - start + 1 < sub_len)
			{
				min_start = start;
				min_end = end;
				sub_len = end - start + 1;
			}

			//break;
		}
	}
	std::cout << "start=" << min_start << ",end=" << min_end << std::endl;
	return 0;
}

/*
 * Problem2:给定字符集合,打印字符全排列
 * @brief: 目前结果集还是有些重复.如3,2,1 会给出8中组合.
 */
void CalAllComb(char A[], int begin, int end, std::vector<std::string> &comb_result)
{
	if (begin == end)
	{
		std::string s;
		s.insert(s.begin(), A[begin]);
		comb_result.push_back(s);
		return;
	}


	for (int t = begin+1; t <= end; t++)//此处应该是一个循环,而不是默认为start
	{
		std::vector<std::string> tmp;
		CalAllComb(A, begin+1, end, tmp);
		for (size_t i = 0; i < tmp.size(); i++)
		{
			comb_result.push_back(A[begin] + tmp[i]);
			comb_result.push_back(tmp[i] + A[begin]);
		}
		if (t != begin)
		    std::swap(A[begin], A[t]);
	}
}

void PrintAllComb(char A[], int len)
{
	std::vector<std::string> comb_result;
	CalAllComb(A, 0, len-1, comb_result);
	std::cout << "size=" << comb_result.size() << std::endl;
	for (size_t i = 0; i < comb_result.size(); i++)
		std::cout << comb_result[i] << std::endl;
}

/*
 * Problem3:给定一个int型,计算用二进制表示的情况下,有多少个1
 * 如:9用二进制表示为1001,由2个1构成
 * @brief:设置一个标记位,然后不断的左移一位,&后计算有多少个1
 */
int PrintBianryNum(int n)
{
	int cnt = 0;
	unsigned int flag = 1;
    while (flag > 0)
    {
    	if (n & flag == 1)
    		cnt++;
    	flag = (flag << 1);
    }
    std::cout << "n=" << n << ",cnt=" << cnt << std::endl;
}
/*
 * @brief:应用一个定理, n & (n-1) 的结果是把n 的最右的1变为0
 */
int PrintBianryNumEx(int n)
{
	int cnt = 0;
	int resume = n;
	while (n > 0)
	{
		cnt++;
		n = n & (n-1);
	}
	std::cout << "n=" << resume << ",cnt=" << cnt << std::endl;
}

/*
 * Problem3: 计算大数的阶乘
 *
 * 数据结构: |cnt|0~9|0~9|0~9|0~9|0~9|
 *             0   1   2   3   4  5
 */
int CalNBigNum(int n)
{
	if (0 == n) return 1;
	if (1 == n) return 1;

	int array[4096] = {0};
	for (int i = 1; i <= n; i++)
	{
		if (array[0] == 0) // first item
		{
			array[0] = 1;
			array[1] = i;
		}
		else
		{
			int pre_idx = 0; //进位下标
			int last_over_value = 0; //地位向高位的进值,10进制内只有一位
			for (int idx = 1; idx <= array[0]; idx++) // 下标
			{
				int item = array[idx] * i + last_over_value;
				//std::cout << "item=" << item << std::endl;

				if (item < 10) //位置原值
				{
					array[idx] = item;
					last_over_value = 0;
				}

				else // 有进位
				{
					array[idx] = item % 10;
					last_over_value = item/10;
				}
				//std::cout << "idx=" << idx << ",pre_idx=" << pre_idx << std::endl;
			}

			if (0 != last_over_value) //只有最高位产生进位时,才需要array[0]+1
			{
				array[0] += 1;
				array[array[0]] = last_over_value;
			}

		}

		/**for (int i = 0; i < 100; i++)
			std::cout << array[i];
		std::cout << std::endl;**/
	}

	std::cout << "cnt=" << array[0] << "," << n << "(!)=";
	for (int i = array[0]; i > 0; i--)
		std::cout << array[i];
	std::cout << std::endl;

	return 0;
}

/*
 * Problem4: 把一个数列中的奇数排到偶数前面
 * 重点是在: 函数指针的传递.可以把判断和函数主体分开,参考 STL中的sort方法.
 */

bool IsOdd(int n)
{
	if (n & 0x01 ==  1)
		return true;
	else
		return false;
}
int SortIntArray(int a[], int len, bool (*func)(int))
{
	std::cout << func(a[0]) << std::endl;
	return 0;
}
