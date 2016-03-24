#pragma once

#include "stdio.h"
#include "time.h"
#include "stdlib.h"

struct point//节点坐标结构体
{
	int x,y;//坐标
};


class AStarMap
{
public:
	int** MAP;
	int map_lenx;
	int map_leny;
	struct point start;
	struct point end;
	
public:
	AStarMap(const int & map_lenx,const int & map_leny,const point & start,const point & end);
	~AStarMap(void);
};

