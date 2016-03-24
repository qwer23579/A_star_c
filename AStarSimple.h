#pragma once

void init_map();
int  scan();
void show_map();//显示地图的函数

struct node//基本节点
{
	int  x,y;//记录在地图中的xy坐标
	int f,g,h;//节点评估值f = 父节点到当前节点的代价g+当前节点到终点的预估代价h，即f=g+h
};

struct point
{
	int x,y;//坐标
};//节点坐标结构体，注意，在此处已生成了开始start，end

class Astack
{
public:
	node data;//栈的每一个数据节点，这个数据节点记录了自己的坐标和评估值f，预估值h，和消耗代价g
	Astack *next;//指向下一个节点的指针
	Astack *futher;//指向父节点，这个非常重要，因为当扫描终点的时候，通过不停反向查询父节点就可以得到了最短路径


public:
	Astack(void);
	~Astack(void);
	int conpute_F(Astack * futher,Astack *p);
	int push(point n,Astack *F = NULL);
	Astack * find_point(point n);
	Astack *get_Fmin();
	int delete_point(Astack *n);//传入要删除的节点地址
	point next_point(point m,int index = 0);

};

