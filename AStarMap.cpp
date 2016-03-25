#include "StdAfx.h"
#include "AStarMap.h"

AStarMap::AStarMap(const int & map_lenx,const int & map_leny,const point & start,const point & end,const int random):
	map_lenx(map_lenx),
	map_leny(map_leny),
	start(start),
	end(end)
{
//初始化地图
	int t = 0;//用来生成随机数
	int x,y;
	//map = (int **)malloc(sizeof(int *)*map_lenx);//动态申请map_lenx个一维数组，并赋值给map
	map = new int *[map_lenx]; 
	for (x = 0 ; x<map_lenx;x++)//对于每个一维数组都要申请map_leny个内存空间
	{
		//map[x] = (int *)malloc(sizeof(int )*map_leny);
		map[x] = new int[map_leny];
	}

	for ( x=  1 ;x<map_lenx-1;x++)//使用双循环对申请的动态二维数组赋值
	{
		for ( y = 1 ; y<map_leny-1 ; y++)
		{	
			if (random == 0)
			{
				//每次都会重置srand(),并且循环调用,造成随机数据重复,将种子移到main()函数里面
				//srand((unsigned)time(NULL)+rand());//置随机种子,不然生成的地图很多时候是一样的
				t = rand()%200;//得到一个200以内的数
				if (t>40)//当t大于40时 = 0，否则 = 1，这样做是为了使可通行的空间多一些，不然太容易形成没通路的地图
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
		for (x= 5 ;x<map_leny-5;x++)//对地图的第零行和最后一行置1，因为是墙壁
		{
			map[5][x] = 1;
			map[map_lenx-6][x] = 1;
		}
		for (y= 5; y<map_lenx-5;y++)//对地图的第零列和最后一列置1，因为是墙壁
		{
			map[y][map_leny-5] = 1;
		}
	}

	for (x= 0 ;x<map_leny;x++)//对地图的第零行和最后一行置1，因为是墙壁
	{
		map[0][x] = 1;
		map[map_lenx-1][x] = 1;
	}
	for (y= 0; y<map_lenx;y++)//对地图的第零列和最后一列置1，因为是墙壁
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
