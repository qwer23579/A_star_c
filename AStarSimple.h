#pragma once
class Astack;

int** init_map(int map_lenx,int map_leny);//��ʼ����ͼ
int  scan(int **MAP,int map_lenx,int map_leny,struct point start,struct point end,Astack open,Astack close);//ɨ�����·��
void show_map(int **MAP,int map_lenx,int map_leny,struct point start,struct point end, Astack open,Astack close);//��ʾ��ͼ�ĺ���

struct node//�����ڵ㣬��������ֵ
{
	int  x,y;//��¼�ڵ�ͼ�е�xy����
	int f,g,h;//�ڵ�����ֵf = ���ڵ㵽��ǰ�ڵ�Ĵ���g+��ǰ�ڵ㵽�յ��Ԥ������h����f=g+h
};

struct point//�ڵ�����ṹ��
{
	int x,y;//����
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
	int conpute_F(Astack * futher,Astack *p,struct point start,struct point end);//����һ���ڵ��Fֵ
	int push(struct point start,struct point end,point n,Astack *F = NULL);//��һ���ڵ����ջ��
	Astack * find_point(point n);//����ջ���Ƿ������nΪ����Ľڵ�
	Astack *get_Fmin();//�õ�һ��f��С�Ľڵ㣬����������ڵ�ĵ�ַ
	int delete_point(Astack *n);//ɾ��ջ��һ���ڵ�
	point next_point(point m,int index = 0);//ͨ����ǰ����m����index��ָʾ�ķ��������һ���ڵ�����

};

