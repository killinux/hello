/*
 * trie.h
 *
 *  Created on: 2012-9-3
 *      Author: kevinguo
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;
class Node
{
public:
	Node():exist(false), belong(false) {}
	bool exist;
	bool belong;
};

/** @input:node[] 存储尺寸不同的n个物品
    @input:K 背包大小
    @output:能塞入背包的序列和最大值.
    @brief: P[i][k].exist = true,对于前i个原始和大小为k的背包存在解
            P[i][k].belong = true,该解包含第i个元素
   */
int GetMaxPack(int node[], int node_len, int K) // 假设node数组从1->n
{
   Node P[node_len+1][K+1];
   P[0][0].exist = true;
   for (int i = 1; i <= K; i++)
	   P[0][i].exist = false;

   for (int i = 1; i <= node_len; i++)
   {
	   for (int k = 0; k <=K; k++)
	   {
		   P[i][k].exist = false; //init
		   if (P[i-1][k].exist) //@brief: 针对一个固定的k,i可以只存一个,如果P[i][k].exist=true; 则所有$>i,P[$][k].exist=true;
		   {
			   P[i][k].exist = true;
			   P[i][k].belong = false;
		   }
		   else if (k - node[i] >= 0)
		   {
			   if (P[i-1][k-node[i]].exist)
			   {
				   P[i][k].exist = true;
				   P[i][k].belong = true;
			   }
		   }
	   }
   }

   // find item which to componse K, P(i,k) = P(i-1,K)和P(i-1,K-Kn)的逆过程
   int remain = K;
   while (remain > 0)
   {
       for (int i = 1; i <= node_len; i++)
       {
    	   if (P[i][remain].belong)
    	   {
    		   std::cout << "i=" << i << ",item=" << node[i] <<",belong=" << P[i][remain].belong << std::endl;
    		   remain -= node[i];
    	   }
       }
   }

   return 0;
}

/***
 * 背包问题的变形,数组中元素可以添加任意个
 */
int GetPackExtra(int node[], int node_len, int K)
{
   Node P[node_len+1][K+1];
   P[0][0].exist = true;
   for (int i = 1; i <= K; i++)
	   P[0][i].exist = false;

   for (int i = 1; i <= node_len; i++)
   {
	   for (int k = 0; k <= K; k++)
	   {
		   P[i][k].exist = false; //init
		   if (P[i-1][k].exist) //@brief: 针对一个固定的k,i可以只存一个,如果P[i][k].exist=true; 则所有$>i,P[$][k].exist=true;
		   {
			   P[i][k].exist = true;
			   P[i][k].belong = false;
		   }
		   else
		   {
			   for (int j = 1; j <= node_len; j++)
			   {
				   if (k - node[j] >= 0)
				   {
					   if (P[i-1][k-node[j]].exist)
					   {
						   P[i][k].exist = true;
						   P[i][k].belong = true;
						   //break;
					   }
				   }
			   }
		   }
	   }
   }
   for (int i = 1; i <= node_len; i++)
   	   std::cout << "i=" << i << ",belong=" << P[i][K].belong <<",exist=" << P[i][K].exist << std::endl;
   return 0;
}


/***
 * 汉诺塔,
 * 核心:缩小问题规模,从规模n推导出n+1
 */
int HanoiTower(int list[], int list_len, char A, char B, char C)
{
	if (list_len == 1)
		std::cout << "move " << list[list_len-1] << " from " << A << " to " << C << std::endl;
	else
	{
		HanoiTower(list, list_len-1, A, C, B);
		std::cout << "move " << list[list_len-1] << " from " << A << " to " << C << std::endl;
		HanoiTower(list, list_len-1, B, A, C);
	}

	return 0;
}

/***
 * 汉诺塔,非递归实现.
 * 主要是用程序栈模拟函数调用栈
 */
class Opt
{
public:
	Opt() {}
	Opt(int _begin, int _end, char _A, char _B, char _C):begin(_begin), end(_end), A(_A), B(_B), C(_C)
	{}
	int operator= (const Opt &r)
	{
		begin = r.begin;
		end = r.end;
		A = r.A;
		B = r.B;
		C = r.C;
		return 0;
	}
	int begin;
	int end;
	char A;
	char B;
	char C;

};
typedef std::stack<Opt> OptQueue;
int HanoiTowerLoop(int list[], int list_len, char A, char B, char C)
{
	OptQueue opt_queue;
	opt_queue.push(Opt(0, list_len-1, A, B, C));
	Opt tmp;
	while (!opt_queue.empty())
	{
		tmp = opt_queue.top();
		opt_queue.pop();
		if (tmp.begin == tmp.end)
		{
			std::cout << "move " << list[tmp.begin] << " from " << tmp.A << " to " << tmp.C << std::endl;
		}
		else
		{
			opt_queue.push(Opt(tmp.begin, tmp.end-1, tmp.B, tmp.A, tmp.C));
			opt_queue.push(Opt(tmp.end, tmp.end, tmp.A, tmp.B, tmp.C));
			opt_queue.push(Opt(tmp.begin, tmp.end-1, tmp.A, tmp.C, tmp.B));
		}
	}
	return 0;
}

/**
 * 汉诺塔变形:不在假定所有盘子都放在一个桩子上,可以任意放在桩子上,仍然保持从小到大的特性,
 * 目的是把这些盘子挪到一个桩子上
 * @brief:
 * 其实和普通的汉诺塔差不太多，也是递归来做。假设我们要把所有盘子移到柱子1上，
 * 有两种可能：一是最大的盘子已经在柱子1了，这时只需要把剩下的盘子移到1上，这就得到了一个同样的但是规模更小的问题，递归处理即可；
 * 二是最大的盘子不在柱子1上，假设最大盘子在柱子2，这时就需要把所有剩下的盘子移到柱子3（这和原问题一样），然后把最大盘子移到1，再把剩下盘子从3移到1（此时剩下的盘子一定已经都在3上排列好了，所以是一个普通汉诺塔问题）
 *
 */
char GetMaxPos(int a, int b, int c)
{
	int tmp = (a>b?a:b);
	int max = tmp>c?tmp:c;
	if (max == a)
		return 'A';
	else if (max == b)
		return 'B';
	else if (max == c)
		return 'C';

	return 0;
}
int HanoiTowerExtra(vector<int> &A, int &a_len, vector<int> &B, int &b_len, vector<int> &C, int &c_len,char to, char bri, char from);
void VectorToArray(int a[], const vector<int> &src);

vector<int> &GetStack(vector<int> &A, vector<int> &B, vector<int> &C, char to)
{
	if (to == 'A')
        return A;
	if (to == 'B')
		return B;
	if (to == 'C')
	    return C;
}
int &GetStackLen(int &a_len, int &b_len, int &c_len, char to)
{
	if (to == 'A')
	    return a_len;
	if (to == 'B')
		return b_len;
	if (to == 'C')
		return c_len;
}
void PrintArrary(int a[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "a[" << i << "]=" << a[i] << endl;
	}
}
void MoveTo(vector<int> &A, int &a_len, vector<int> &B, int &b_len, vector<int> &C, int &c_len,
		char to, char bri, char from)
{
	if (GetStackLen(a_len, b_len, c_len, from) == 1)
	{
		cout << "move " << GetStack(A,B,C,from)[0] << " from " << from << " to " << to << endl;
		vector<int> &tmp = GetStack(A,B,C,from);
		GetStack(A,B,C,to).insert(GetStack(A,B,C,to).begin(),tmp.begin(),tmp.end());
		GetStackLen(a_len, b_len, c_len, to) += GetStackLen(a_len, b_len, c_len, from);
		tmp.clear();
		int *array = new int[GetStackLen(a_len, b_len, c_len, to)];
		for (int i = 0; i < GetStackLen(a_len, b_len, c_len, to); i++)
			array[i] = GetStack(A,B,C,to)[i];
		//PrintArrary(array, GetStackLen(a_len, b_len, c_len, to));
		HanoiTower(array, GetStackLen(a_len, b_len, c_len, to), to, from, bri);
	}
	else
	{
	    HanoiTowerExtra(A, a_len, B, b_len, C, c_len, to, bri, from);
	}
}



int HanoiTowerExtra(vector<int> &A, int &a_len, vector<int> &B, int &b_len, vector<int> &C, int &c_len,
		char to, char bri, char from)
{
	char max_pos = GetMaxPos(A[a_len-1],B[b_len-1],C[c_len-1]);
	cout << "max_pos=" << max_pos << endl;
	if (max_pos == to)
	{
		GetStackLen(a_len, b_len, c_len, to)--;
		if (GetStack(A,B,C,bri)[0] > GetStack(A,B,C,from)[0])
		    MoveTo(A, a_len, B, b_len, C, c_len, bri, to, from);
		else
			MoveTo(A, a_len, B, b_len, C, c_len, from, to, bri);
	}
	/*
	else
	{
		if (max_pos == bri)
		{
			MoveTo(A, a_len, B, b_len, C, c_len, from, to, bri);
			std::cout << "move " << GetStack(A,B,C,bri).back() << "from " << bri << " to " << to << std::endl;
			GetStackLen(a_len, b_len, c_len, to)++;
			vector<int> tmp = GetStack(A,B,C,from);
			int aa[10];
			VectorToArray(aa, tmp);
			HanoiTower(aa, tmp.size(), from, bri, to);
			GetStack(A,B,C,to).insert(GetStack(A,B,C,to).begin(),tmp.begin(),tmp.end());
			GetStackLen(a_len, b_len, c_len, to) += tmp.size();
		}
		else if (max_pos == from)
		{
			MoveTo(A, a_len, B, b_len, C, c_len, bri, to, from);
			std::cout << "move " << GetStack(A,B,C,from).back() << "from " << bri << " to " << to << std::endl;
			vector<int> tmp = GetStack(A,B,C,bri);
			int aa[10];
			VectorToArray(aa, tmp);
			HanoiTower(aa, tmp.size(), bri, from, to);
			GetStack(A,B,C,to).insert(GetStack(A,B,C,to).begin(),tmp.begin(),tmp.end());
			GetStackLen(a_len, b_len, c_len, to) += tmp.size();
		}
	}
	*/
	return 0;
}

void VectorToArray(int a[], const vector<int> &src)
{
	for (size_t i = 0; i < src.size(); i++)
		a[i] = src[i];
}
#endif /* TRIE_H_ */
