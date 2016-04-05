#pragma once
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include <iostream>
#include "AStarMap.h"

#define TESTMODEL

const int VertV = 10;
const int TiltV = 14;

class Astack;

int scan(AStarMap & A_map,Astack & open,Astack & close);//扫描最短路径
void show_map(AStarMap & A_map,Astack & open,Astack & close);//显示地图的函数

#ifdef TESTMODEL
void show_error_map(AStarMap & A_map, Astack & open,Astack & close);//显示地图的函数
#endif


struct node//基本节点，包含评估值
{
	int  x,y;//记录在地图中的xy坐标
	int f,g,h;//节点评估值f = 父节点到当前节点的代价g+当前节点到终点的预估代价h，即f=g+h
	struct node * next;
	struct node * futher;
};

class Astack
{
public:
	//node data;//栈的每一个数据节点，这个数据节点记录了自己的坐标和评估值f，预估值h，和消耗代价g
	struct node * head;
	//Astack *next;//指向下一个节点的指针
	//Astack *futher;//指向父节点，这个非常重要，因为当扫描终点的时候，通过不停反向查询父节点就可以得到了最短路径

public:
	Astack(void);
	~Astack(void);
	int conpute_F(const point & start,const point & end,node * p,node * futher);//计算一个节点的F值
	int push(const point & start,const point & end,const point & point_n,node *F = NULL);//将一个新节点节点加入栈中（open列表）
	int push(node *node_p);//将一个已有节点加入栈中(用于close列表)
	node * find_point(const point & point_n);//查找栈中是否存在以n为坐标的节点
	node * get_Fmin();//得到一个f最小的节点，并返回这个节点的地址
	int delete_point(node *node_p);//删除栈中一个节点，但是不释放。因为open中删除后会放入另外一个栈close中
	point next_point(const point & point_n,int index = 0);//通过当前坐标m、和index所指示的方向计算下一个节点坐标
};

