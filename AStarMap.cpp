#include "StdAfx.h"
#include "AStarMap.h"

AStarMap::AStarMap(const int & map_lenx,const int & map_leny,const point & start,const point & end,const int random):
	map_lenx(map_lenx),
	map_leny(map_leny),
	start(start),
	end(end)
{
//��ʼ����ͼ
	int t = 0;//�������������
	int x,y;
	//map = (int **)malloc(sizeof(int *)*map_lenx);//��̬����map_lenx��һά���飬����ֵ��map
	map = new int *[map_lenx]; 
	for (x = 0 ; x<map_lenx;x++)//����ÿ��һά���鶼Ҫ����map_leny���ڴ�ռ�
	{
		//map[x] = (int *)malloc(sizeof(int )*map_leny);
		map[x] = new int[map_leny];
	}

	for ( x=  1 ;x<map_lenx-1;x++)//ʹ��˫ѭ��������Ķ�̬��ά���鸳ֵ
	{
		for ( y = 1 ; y<map_leny-1 ; y++)
		{	
			if (random == 0)
			{
				//ÿ�ζ�������srand(),����ѭ������,�����������ظ�,�������Ƶ�main()��������
				//srand((unsigned)time(NULL)+rand());//���������,��Ȼ���ɵĵ�ͼ�ܶ�ʱ����һ����
				t = rand()%200;//�õ�һ��200���ڵ���
				if (t>40)//��t����40ʱ = 0������ = 1����������Ϊ��ʹ��ͨ�еĿռ��һЩ����Ȼ̫�����γ�ûͨ·�ĵ�ͼ
				{
					map[x][y] = 0;
				}
				else
				{
					map[x][y]  = 1;
				}
			}
			else
			{
				map[x][y] = 0;
			}
		}
	}
	if (random != 0)
	{
		for (x= 5 ;x<map_leny-5;x++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
		{
			map[5][x] = 1;
			map[map_lenx-6][x] = 1;
		}
		for (y= 5; y<map_lenx-5;y++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
		{
			map[y][map_leny-5] = 1;
		}
	}

	for (x= 0 ;x<map_leny;x++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
	{
		map[0][x] = 1;
		map[map_lenx-1][x] = 1;
	}
	for (y= 0; y<map_lenx;y++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
	{
		map[y][0] = 1;
		map[y][map_leny-1] = 1;
	}
}


AStarMap::~AStarMap(void)
{
	for ( int x = 0 ; x<map_lenx;x++)
	{
		delete[] map[x];
	}
	delete[] map;
}
