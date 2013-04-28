/*
 * kinds_sort.h
 *
 *  Created on: 2012-11-20
 *      Author: kevinguo
 */

#ifndef KINDS_SORT_H_
#define KINDS_SORT_H_

#include <math.h>
#include <queue>
#include <vector>

/*
 * 基数排序(降序)
 * @output: k表示每个元素有k位
 */
static const int SCALE = 10;//表示10进制
void PrintQueue(queue<int> global_queue)
{
	while (!global_queue.empty())
	{
		cout << global_queue.front() << ",";
		global_queue.pop();
	}
	cout << endl;
}
int GetIdxFromInt(int i, int pos)
{
	int idx = i/(pow(10, pos));
	idx %= 10;
    //cout << "GetIdxFromInt:i=" << i << ",idx=" << idx << endl;
	return idx;
}
int RadixSort(int array[], int len, int k)
{
	queue<int> global_queue;
	for (int i = 0; i < len; i++)
		global_queue.push(array[i]);
	PrintQueue(global_queue);

	queue<int> scale_queue[SCALE];

	for (int i = 1; i <= k; i++)
	{
		while (!global_queue.empty())
		{
			int idx = GetIdxFromInt(global_queue.front(), i-1);
			//cout << global_queue.front() << "," << idx << endl;
			scale_queue[idx].push(global_queue.front());
			global_queue.pop();
		}
		for (int t = 0; t < SCALE; t++)
		{
			while (!scale_queue[t].empty())
			{
				global_queue.push(scale_queue[t].front());
				scale_queue[t].pop();
			}
		}
	}
	PrintQueue(global_queue);
	return 0;
}

void PrintArray(int a[], int len)
{
	for (int i = 0; i < len; i++)
		cout << a[i] << ",";
	cout << endl;
}

/*
 * 快速排序,每次从中间位置,分割成两部分
 */

int _MergeSort(int a[], int left, int right)
{
	if (right - left == 1)
	{
		if (a[left] > a[right])
			swap(a[left], a[right]);
	}
	else if (right != left)
	{
		int middle = (left + right)/2;
		_MergeSort(a, left, middle - 1);
		_MergeSort(a, middle, right);

		vector<int> tmp;
		int i = left;
		int j = middle;
		while ((i <= middle - 1) && (j <= right))
		{
			if (a[i] < a[j])
			{
				tmp.push_back(a[i]);
				i++;
			}
			else
			{
				tmp.push_back(a[j]);
				j++;
			}
		}
		if (j > right) //左边有剩余
		{
			for (int t = 0; t <= (left - i); t++)
				a[right - t] = a[middle - 1 - t];
		}
		for (size_t t = 0; t < tmp.size(); t++)
			a[left+t] = tmp[t];
	}
	return 0;
}
void MergeSort(int a[], int len)
{
	PrintArray(a, len);
	_MergeSort(a, 0, len - 1);
	PrintArray(a, len);
}

/*
 * 快速排序,每次选取第一个位置进行比较,然后比较交换后切分为两个子问题,后续递归求解
 */
int Partition(int a[], int left, int right)
{
	int divit = a[left];
	int i = left;
	int j = right;
	while (j > i)
	{
	    while ((a[i] <= divit) && (i <= right)) i++;
	    while ((a[j] > divit) && (j >= left)) j--;

	    if (j >= i)
	        swap(a[i], a[j]);
	}

	int middle = j;
	swap(a[left], a[middle]);
	return middle;
}

int _QuickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int middle = Partition(a, left, right);
		//PrintArray(a, right+1);
		_QuickSort(a, left, middle - 1);
		_QuickSort(a, middle + 1, right);
	}
	return 0;
}

int QuickSort(int a[], int len)
{
	PrintArray(a, len);
	_QuickSort(a, 0, len - 1);
	PrintArray(a, len);
	return 0;
}


int Select(int a[], int left, int right, int k)
{
	if (left == right)
		cout << "a[k]=" << a[left] << endl;
	else
	{
		int middle = Partition(a, left, right);
		if (middle - left +1 >= k)
			Select(a, left, middle, k);
		else
			Select(a, middle + 1, right, k - (middle - left +1));
	}
	return 0;
}
/*
 * 查找第K个小的数,比较次数O(n),参见P103
 */
int FindMinK(int a[], int len, int idx_k)
{
	if ((idx_k < 0) || (idx_k > len-1))
		return 0;
	Select(a, 0, len - 1, idx_k);

	return 0;
}


/*
 * 堆排序,采用自底向上建堆,参见P101,复杂度为O(n)
 * @brief:数组下标从1开始
 */
int HeapSort(int a[], int len)
{
	PrintArray(a, len);

	for (int i = len/2; i > 0; i--)
	{
		int j = i;
		while (2 * j <= len)
		{

			if (2*j+1 <= len)
			{
				//cout << "j=" << j << ",a[j]=" << a[j] << ",a[2j]=" << a[2*j] << ",a[2j+1]=" << a[2*j+1] << endl;
				if (a[2*j] > a[2*j+1])
				{
					if (a[j] < a[2*j])
						swap(a[j],a[2*j]);
					j = 2*j;
				}
				else if (a[2*j+1] > a[2*j])
				{
					if (a[j] < a[2*j+1])
						swap(a[j],a[2*j+1]);
					j = 2*j + 1;
				}
			}
			else
			{
				//cout << "j=" << j << ",a[j]=" << a[j] << ",a[2j]=" << a[2*j] << endl;
				if (a[j] < a[2*j])
					swap(a[j],a[2*j]);
				j = 2*j;
			}
		}
	}

	cout << "int HeapSort(int a[], int len)" << endl;
	PrintArray(a, len);
	return 0;
}

#endif /* KINDS_SORT_H_ */
