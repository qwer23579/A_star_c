#pragma once

void init_map();
int  scan();
void show_map();//��ʾ��ͼ�ĺ���

struct node//�����ڵ�
{
	int  x,y;//��¼�ڵ�ͼ�е�xy����
	int f,g,h;//�ڵ�����ֵf = ���ڵ㵽��ǰ�ڵ�Ĵ���g+��ǰ�ڵ㵽�յ��Ԥ������h����f=g+h
};

struct point
{
	int x,y;//����
};//�ڵ�����ṹ�壬ע�⣬�ڴ˴��������˿�ʼstart��end

class Astack
{
public:
	node data;//ջ��ÿһ�����ݽڵ㣬������ݽڵ��¼���Լ������������ֵf��Ԥ��ֵh�������Ĵ���g
	Astack *next;//ָ����һ���ڵ��ָ��
	Astack *futher;//ָ�򸸽ڵ㣬����ǳ���Ҫ����Ϊ��ɨ���յ��ʱ��ͨ����ͣ�����ѯ���ڵ�Ϳ��Եõ������·��


public:
	Astack(void);
	~Astack(void);
	int conpute_F(Astack * futher,Astack *p);
	int push(point n,Astack *F = NULL);
	Astack * find_point(point n);
	Astack *get_Fmin();
	int delete_point(Astack *n);//����Ҫɾ���Ľڵ��ַ
	point next_point(point m,int index = 0);

};

