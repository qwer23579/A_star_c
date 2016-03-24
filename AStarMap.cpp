#include "StdAfx.h"
#include "AStarMap.h"

AStarMap::AStarMap(const int & map_lenx,const int & map_leny,const point & start,const point & end):
	map_lenx(map_lenx),
	map_leny(map_leny),
	start(start),
	end(end)
{
	//��ʼ����ͼ
	int t = 0;//�������������
	int x,y;
	MAP = (int **)malloc(sizeof(int *)*map_lenx);//��̬����map_lenx��һά���飬����ֵ��MAP
	for (x = 0 ; x<map_lenx;x++)//����ÿ��һά���鶼Ҫ����map_leny���ڴ�ռ�
	{
		MAP[x] = (int *)malloc(sizeof(int )*map_leny);
	}
	for ( x=  0 ;x<map_lenx;x++)//ʹ��˫ѭ��������Ķ�̬��ά���鸳ֵ
	{
		for ( y = 0 ; y<map_leny ; y++)
		{	
			if (y==0||y==map_leny-1)//��0�к����һ����Զ����1����Ϊ��ǽ��
			{
				MAP[x][y] = 1;
				continue;
			}
			//ÿ�ζ�������srand(),����ѭ������,�����������ظ�,�������Ƶ�main()��������
			//srand((unsigned)time(NULL)+rand());//���������,��Ȼ���ɵĵ�ͼ�ܶ�ʱ����һ����
			t = rand()%200;//�õ�һ��200���ڵ���
			if (t>40)//��t����40ʱ = 0������ = 1����������Ϊ��ʹ��ͨ�еĿռ��һЩ����Ȼ̫�����γ�ûͨ·�ĵ�ͼ
			{
				MAP[x][y] = 0;
			}
			else
			{
				MAP[x][y]  = 1;
			}
		}
	}
	for (x= 0 ;x<map_leny;x++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
	{
		MAP[0][x] = 1;
		MAP[map_lenx-1][x] = 1;
	}
}


AStarMap::~AStarMap(void)
{
}
