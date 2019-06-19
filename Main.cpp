#include <iostream>
#include "LinkList.h"
//��ȡFֵ
#define GET_F(g, h) ((g + h) * 5)
//��ȡ����ֵ
#define ABS(a, b) (a > b ? a - b : b - a)

struct _NODE
{
	int index;
	int f_index;
	int g;
	int h;
};
//Ѱ·�㷨
int FindPath(int* map, int w, int h, int begin, int end, int* OutPath, bool Dir = 0)
{
	//����
	CLinkList<_NODE> OpenList;
	//�ձ�
	CLinkList<_NODE> CloseList;
	//�������뿪��
	_NODE BeginNode;
	BeginNode.f_index = -1;
	BeginNode.index = begin;
	BeginNode.g = 0;
	BeginNode.h = 0;
	OpenList.Push(BeginNode);

	//�෽������
	int fx = 4;
	if (Dir)
		fx = 8;
	//x,yƫ����
	int offx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
	int offy[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

	//Ѱ·�㷨
	while (OpenList.Length())
	{
		//�ӿ����� �ҵ�һ��Fֵ��С�Ľڵ� ����ձ� ��Ϊ��׼
		_NODE* SmallNode;
		SmallNode = OpenList.Get(0);
		CloseList.Push(*SmallNode);
		OpenList.Erase(0);
		SmallNode = CloseList.Get(CloseList.Length() - 1);
		//������ڵ�Ϊ��׼ ����N����Ѱ·
		int x = SmallNode->index % w;
		int y = SmallNode->index / w;

		// 0 ��  1 ��  2 ��  3 ��
		// 4 ����  5 ����  6 ����  7 ����
		for (int i = 0; i < fx; ++i)
		{
			//Խ���ж�
			int xTmp = x + offx[i];
			int yTmp = y + offy[i];
			if (xTmp < 0 || xTmp >= w || yTmp < 0 || yTmp >= h)
				continue;
			int CurIndex = xTmp + yTmp * w;
			//1 ��·  0 ͨ·
			if (map[CurIndex])
				continue;
			//�Ƿ����յ� ������յ���ô��ʼ����·��
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
			//�Ƿ��ڱ��б��
			bool inlist = 0;
			//����Ƿ��ڱձ�
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
			//��ǰGֵ
			int CurG;
			if (i < 4)
				CurG = SmallNode->g + 5;
			else
				CurG = SmallNode->g + 7;

			//����Ƿ��ڿ���
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
			//�뿪��
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
	//����
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
				std::cout << "��";
			else if (map[i] == 1)
				std::cout << "��";
			else
				std::cout << "  ";
			if (i % w == w - 1)
				std::cout << "\n";
		}
		system("pause");
	}
}