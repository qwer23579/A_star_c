#pragma once

#include "stdio.h"
#include "time.h"
#include "stdlib.h"

struct point//�ڵ�����ṹ��
{
	int x,y;//����
};


class AStarMap
{
public:
	int** map;
	int map_lenx;
	int map_leny;
	struct point start;
	struct point end;
	
public:
	AStarMap(const int & map_lenx,const int & map_leny,const point & start,const point & end,const int random);
	~AStarMap(void);
};

