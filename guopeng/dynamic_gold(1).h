/*
 * dynamic_gold.h
 *
 *  Created on: 2012-7-15
 *      Author: kevinguo
 */


/**
 * ��ô������������ö�̬�滮ȥ����أ���������ķ������ǿ��԰�������Ĳ���ȥ���ǣ�

       1��������������Ӧ�Ĺ��̡�
       2��˼�����̵����һ�����裬��������Щѡ�������
       3���ҵ����һ���������⣬ȷ�����ϡ��������ص��������������в���ͬ�ĵط�����Ϊ������
       4��ʹ����������ϡ������ӽṹ����
       5���ҵ��߽磬���Ǳ߽�ĸ��ִ���ʽ��
       6��ȷ�����㡰�������������һ����ԣ�����������ڶ����������ѡ��һ����Ϊʵʩ������������ͬʱʵʩ�����������ô��������Ƕ����ġ�
       7���������������¼��
       8����������ʱ���Ƿ�����Ҫ��
       9��д��ת�Ʒ���ʽ��
�ο�: http://www.cnblogs.com/sdjl/articles/1274312.html . very Good.
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
		// �߽�
		if (mine_idx == 0)
		{
			if (min[mine_idx].need_people <= curr_people)
			    return min[mine_idx].value;
		    else
			    return 0;
		}
        // ��������������Ļ�,
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
		// �������������Ƿ�֮ǰ�Ѿ������,������,ֱ�ӷŻ�.
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
	int sub_max_value[3][3]; // ����������Ž�,��������,�ɱ����ظ�����!!!
	int x;
	int y;
};


#endif /* DYNAMIC_GOLD_H_ */
