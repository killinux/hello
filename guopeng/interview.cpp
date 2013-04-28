#include <iostream>
#include "interview.h"

using namespace std;

/*
 * Problem1:
 * desc: �����ַ���A���ַ�����B,��A�в��Ұ���B�������ַ�������Ӵ�
 * solution: ��A�趨��ʼλ��,i=0,end=b_len,Ȼ�� end�������ɨ��,
 *       ��i->end����Ӵ�����Bʱ,�ڲ鿴i�Ƿ���Ҫ,����Ҫ(����B��Ҫ���ַ�,����i->end������ͬ�ַ�),��ʱi++
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
 * Problem2:�����ַ�����,��ӡ�ַ�ȫ����
 * @brief: Ŀǰ�����������Щ�ظ�.��3,2,1 �����8�����.
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


	for (int t = begin+1; t <= end; t++)//�˴�Ӧ����һ��ѭ��,������Ĭ��Ϊstart
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
 * Problem3:����һ��int��,�����ö����Ʊ�ʾ�������,�ж��ٸ�1
 * ��:9�ö����Ʊ�ʾΪ1001,��2��1����
 * @brief:����һ�����λ,Ȼ�󲻶ϵ�����һλ,&������ж��ٸ�1
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
 * @brief:Ӧ��һ������, n & (n-1) �Ľ���ǰ�n �����ҵ�1��Ϊ0
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
 * Problem3: ��������Ľ׳�
 *
 * ���ݽṹ: |cnt|0~9|0~9|0~9|0~9|0~9|
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
			int pre_idx = 0; //��λ�±�
			int last_over_value = 0; //��λ���λ�Ľ�ֵ,10������ֻ��һλ
			for (int idx = 1; idx <= array[0]; idx++) // �±�
			{
				int item = array[idx] * i + last_over_value;
				//std::cout << "item=" << item << std::endl;

				if (item < 10) //λ��ԭֵ
				{
					array[idx] = item;
					last_over_value = 0;
				}

				else // �н�λ
				{
					array[idx] = item % 10;
					last_over_value = item/10;
				}
				//std::cout << "idx=" << idx << ",pre_idx=" << pre_idx << std::endl;
			}

			if (0 != last_over_value) //ֻ�����λ������λʱ,����Ҫarray[0]+1
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
 * Problem4: ��һ�������е������ŵ�ż��ǰ��
 * �ص�����: ����ָ��Ĵ���.���԰��жϺͺ�������ֿ�,�ο� STL�е�sort����.
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
