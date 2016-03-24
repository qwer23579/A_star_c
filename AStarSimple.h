#pragma once
class Astack;

int** init_map(int map_lenx,int map_leny);//初始化地图
int  scan(int **MAP,int map_lenx,int map_leny,struct point start,struct point end,Astack open,Astack close);//扫描最短路径
void show_map(int **MAP,int map_lenx,int map_leny,struct point start,struct point end, Astack open,Astack close);//显示地图的函数

struct node//基本节点，包含评估值
{
	int  x,y;//记录在地图中的xy坐标
	int f,g,h;//节点评估值f = 父节点到当前节点的代价g+当前节点到终点的预估代价h，即f=g+h
};

struct point//节点坐标结构体
{
	int x,y;//坐标
};

class Astack
{
public:
	node data;//栈的每一个数据节点，这个数据节点记录了自己的坐标和评估值f，预估值h，和消耗代价g
	Astack *next;//指向下一个节点的指针
	Astack *futher;//指向父节点，这个非常重要，因为当扫描终点的时候，通过不停反向查询父节点就可以得到了最短路径

public:
	Astack(void);
	~Astack(void);
	int conpute_F(Astack * futher,Astack *p,struct point start,struct point end);//计算一个节点的F值
	int push(struct point start,struct point end,point n,Astack *F = NULL);//将一个节点加入栈中
	Astack * find_point(point n);//查找栈中是否存在以n为坐标的节点
	Astack *get_Fmin();//得到一个f最小的节点，并返回这个节点的地址
	int delete_point(Astack *n);//删除栈中一个节点
	point next_point(point m,int index = 0);//通过当前坐标m、和index所指示的方向计算下一个节点坐标

};

