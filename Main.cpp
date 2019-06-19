#include <iostream>
#include "LinkList.h"
//获取F值
#define GET_F(g, h) ((g + h) * 5)
//获取绝对值
#define ABS(a, b) (a > b ? a - b : b - a)

struct _NODE
{
	int index;
	int f_index;
	int g;
	int h;
};
//寻路算法
int FindPath(int* map, int w, int h, int begin, int end, int* OutPath, bool Dir = 0)
{
	//开表
	CLinkList<_NODE> OpenList;
	//闭表
	CLinkList<_NODE> CloseList;
	//将起点存入开表
	_NODE BeginNode;
	BeginNode.f_index = -1;
	BeginNode.index = begin;
	BeginNode.g = 0;
	BeginNode.h = 0;
	OpenList.Push(BeginNode);

	//多方向设置
	int fx = 4;
	if (Dir)
		fx = 8;
	//x,y偏移量
	int offx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
	int offy[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

	//寻路算法
	while (OpenList.Length())
	{
		//从开表中 找到一个F值最小的节点 放入闭表 作为基准
		_NODE* SmallNode;
		SmallNode = OpenList.Get(0);
		CloseList.Push(*SmallNode);
		OpenList.Erase(0);
		SmallNode = CloseList.Get(CloseList.Length() - 1);
		//以这个节点为基准 进行N方向寻路
		int x = SmallNode->index % w;
		int y = SmallNode->index / w;

		// 0 上  1 下  2 左  3 右
		// 4 左上  5 右上  6 左下  7 右下
		for (int i = 0; i < fx; ++i)
		{
			//越界判断
			int xTmp = x + offx[i];
			int yTmp = y + offy[i];
			if (xTmp < 0 || xTmp >= w || yTmp < 0 || yTmp >= h)
				continue;
			int CurIndex = xTmp + yTmp * w;
			//1 死路  0 通路
			if (map[CurIndex])
				continue;
			//是否是终点 如果是终点那么开始整合路径
			if (CurIndex == end)
			{
				int len = 1;
				OutPath[0] = CurIndex;
				int f = SmallNode->index;
				for (int i = CloseList.Length() - 1; i >= 0; --i)
				{
					_NODE* p = CloseList.Get(i);
					if (p->index == begin)
					{
						OutPath[len++] = p->index;
						for (int i = 0; i < len / 2; ++i)
						{
							int iTmp = OutPath[len - 1 - i];
							OutPath[len - 1 - i] = OutPath[i];
							OutPath[i] = iTmp;
						}
						return len;
					}
					if (f == p->index)
					{
						OutPath[len++] = p->index;
						f = p->f_index;
					}
				}
			}
			//是否在表中标记
			bool inlist = 0;
			//检测是否在闭表
			for (int j = 0; j < CloseList.Length(); ++j)
			{
				if (CurIndex == CloseList.Get(j)->index)
				{
					inlist = 1;
					break;
				}
			}
			if (inlist)
				continue;
			//当前G值
			int CurG;
			if (i < 4)
				CurG = SmallNode->g + 5;
			else
				CurG = SmallNode->g + 7;

			//检测是否在开表
			for (int j = 0; j < OpenList.Length(); ++j)
			{
				_NODE n = *OpenList.Get(j);
				if (CurIndex == n.index)
				{
					if (CurG < n.g)
					{
						n.g = CurG;
						n.f_index = CurIndex;
						OpenList.Erase(j);
						int pos;
						for (pos = i - 1; pos >= 0; --pos)
						{
							_NODE* p = OpenList.Get(pos);
							if (GET_F(n.g, n.h) > GET_F(p->g, p->h))
							{
								pos += 1;
							}
						}
						OpenList.Insert(n, pos);
					}
					inlist = 1;
					break;
				}
			}
			if (inlist)
				continue;
			//入开表
			_NODE n;
			n.index = CurIndex;
			n.f_index = SmallNode->index;
			n.g = CurG;
			n.h = (ABS(end % w, CurIndex % w) + ABS(end / w, CurIndex / w)) * 5;
			int pos;
			for (pos = 0; pos < OpenList.Length(); ++pos)
			{
				_NODE* p = OpenList.Get(pos);
				if (GET_F(n.g, n.h) < GET_F(p->g, p->h))
					break;
			}
			OpenList.Insert(n, pos);
		}
	}
	return 0;
}

void main()
{
	//测试
	int w = 10;
	int h = 10;
	const int s = 100;
	int map[s] =
	{
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,1,1,1,1,0,1,
		1,1,0,0,1,1,1,1,0,1,
		1,1,0,1,1,1,1,1,0,1,
		1,1,0,0,0,0,1,1,0,1,
		1,1,1,1,0,0,1,1,0,1,
		1,1,1,1,0,0,1,1,0,1,
		1,1,1,1,0,0,0,0,0,1,
		1,1,1,1,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
	};
	int OutPath[s] = {};
	int len = FindPath(map, w, h, 12, 18, OutPath);
	int Hero;
	int pos = 0;
	while (pos < len)
	{
		system("cls");
		Hero = OutPath[pos++];
		for (int i = 0; i < s; ++i)
		{
			if (Hero == i)
				std::cout << "▲";
			else if (map[i] == 1)
				std::cout << "■";
			else
				std::cout << "  ";
			if (i % w == w - 1)
				std::cout << "\n";
		}
		system("pause");
	}
}