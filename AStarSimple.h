#pragma once
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "AStarMap.h"

const int VertV = 10;
const int TiltV = 14;

class Astack;

int  scan(AStarMap & A_map,Astack & open,Astack & close);//ɨ�����·��
void show_map(AStarMap & A_map, Astack & open,Astack & close);//��ʾ��ͼ�ĺ���

struct node//�����ڵ㣬��������ֵ
{
	int  x,y;//��¼�ڵ�ͼ�е�xy����
	int f,g,h;//�ڵ�����ֵf = ���ڵ㵽��ǰ�ڵ�Ĵ���g+��ǰ�ڵ㵽�յ��Ԥ������h����f=g+h
};

class Astack
{
public:
	node data;//ջ��ÿһ�����ݽڵ㣬������ݽڵ��¼���Լ������������ֵf��Ԥ��ֵh�������Ĵ���g
	Astack *next;//ָ����һ���ڵ��ָ��
	Astack *futher;//ָ�򸸽ڵ㣬����ǳ���Ҫ����Ϊ��ɨ���յ��ʱ��ͨ����ͣ�����ѯ���ڵ�Ϳ��Եõ������·��

public:
	Astack(void);
	~Astack(void);
	int conpute_F(const point & start,const point & end,Astack * p,Astack * futher);//����һ���ڵ��Fֵ
	int push(const point & start,const point & end,const point & point_n,Astack *F = NULL);//��һ���ڵ����ջ��
	Astack * find_point(const point & point_n);//����ջ���Ƿ������nΪ����Ľڵ�
	Astack *get_Fmin();//�õ�һ��f��С�Ľڵ㣬����������ڵ�ĵ�ַ
	int delete_point(Astack *Astack_p);//ɾ��ջ��һ���ڵ�
	point next_point(const point & point_n,int index = 0);//ͨ����ǰ����m����index��ָʾ�ķ��������һ���ڵ�����

};

