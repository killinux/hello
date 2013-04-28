/*
 * dynamic_gold.h
 *
 *  Created on: 2012-7-15
 *      Author: kevinguo
 */


/**
 * 那么遇到问题如何用动态规划去解决呢？根据上面的分析我们可以按照下面的步骤去考虑：

       1、构造问题所对应的过程。
       2、思考过程的最后一个步骤，看看有哪些选择情况。
       3、找到最后一步的子问题，确保符合“子问题重叠”，把子问题中不相同的地方设置为参数。
       4、使得子问题符合“最优子结构”。
       5、找到边界，考虑边界的各种处理方式。
       6、确保满足“子问题独立”，一般而言，如果我们是在多个子问题中选择一个作为实施方案，而不会同时实施多个方案，那么子问题就是独立的。
       7、考虑如何做备忘录。
       8、分析所需时间是否满足要求。
       9、写出转移方程式。
参考: http://www.cnblogs.com/sdjl/articles/1274312.html . very Good.
 */

#ifndef DYNAMIC_GOLD_H_
#define DYNAMIC_GOLD_H_

#include <stdio.h>

class GetMaxGold
{
public:
	GetMaxGold(int _total, int _num)
	: total_people(_total), gold_num(_num)
	{
		min = new MineDate[gold_num];
		min[0].need_people = 77;
		min[0].value = 92;
		min[1].need_people = 22;
		min[1].value = 22;
		min[2].need_people = 29;
		min[2].value = 87;
		min[3].need_people = 50;
		min[3].value = 46;
		min[4].need_people = 90;
		min[4].value = 90;
	}

	int GetMaxValue(int curr_people, int mine_idx)
	{
		// 边界
		if (mine_idx == 0)
		{
			if (min[mine_idx].need_people <= curr_people)
			    return min[mine_idx].value;
		    else
			    return 0;
		}
        // 如果够开采人数的话,
        if (min[mine_idx].need_people <= curr_people)
        {
		    int value1 = GetMaxValue(curr_people - min[mine_idx].need_people, mine_idx - 1) + min[mine_idx].value;
		    int value2 = GetMaxValue(curr_people, mine_idx - 1);
		    return (value1 > value2)?value1:value2;
        }
        else
        {
        	return GetMaxValue(curr_people, mine_idx - 1);
        }

	}

private:
	int total_people;
	int gold_num;
	typedef struct _MineDate
	{
	    int need_people;
	    int value;

	}MineDate;

	MineDate *min;
};

class GetMaxRice
{
public:
	GetMaxRice(int _x, int _y):x(_x),y(_y)
	{
        rice[0][0] = 0;
        rice[0][1] = 1;
        rice[0][2] = 10;
        rice[1][0] = 2;
        rice[1][1] = 3;
        rice[1][2] = 1;
        rice[2][0] = 1;
        rice[2][1] = 1;
        rice[2][2] = 2;
        for (int i = 0; i < 3; i++)
        	for (int j = 0; j < 3; j++)
        		sub_max_value[i][j] = -1;
	}
	int GetMaxValue(int x, int y)
	{
		// 检查这个子问题是否之前已经计算过,如计算过,直接放回.
		if (sub_max_value[x][y] != -1)
			return sub_max_value[x][y];

		if (y == 0)
		{
			if (x == 0)
				return 0;
			else
				sub_max_value[x][y] = GetMaxValue(x-1, y) + rice[x][y];
				return sub_max_value[x][y];
		}
		if (x == 0)
		{
			if (y == 0)
				return 0;
			else
				sub_max_value[x][y] = GetMaxValue(x, y-1) + rice[x][y];
				return sub_max_value[x][y];
		}

		int value1 = GetMaxValue(x-1, y) + rice[x][y];
		int value2 = GetMaxValue(x, y-1) + rice[x][y];
		sub_max_value[x][y] = (value1 > value2) ? value1 : value2;
		return sub_max_value[x][y];
	}
private:
	int rice[3][3];
	int sub_max_value[3][3]; // 子问题的最优解,保存下来,可避免重复计算!!!
	int x;
	int y;
};


#endif /* DYNAMIC_GOLD_H_ */
