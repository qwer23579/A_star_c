#include "StdAfx.h"
#include "AStarSimple.h"


Astack::Astack(void)
{
	next = NULL;
	futher = NULL;
}

Astack::~Astack(void)
{
}

int Astack::conpute_F(const point & start,const point & end,Astack *p,Astack * futher)
{
	if (p->data.x==start.x&&p->data.y==start.y||futher==NULL)//������׽ڵ�Ϊ�գ���ǰ�ڵ�Ϊ���
	{
		p->data.g = 0;
		p->data.h = 0;//��f��gֵ��0����hֵ�û�����Ϊ��Զ����ʹ�õ���������ʲôֵ����ν
		p->data.f =0;
		return 1;
	}
	p->data.g = futher->data.g+1;//��ǰ�ڵ��gֵ�ܱȸ��ڵ��gֵ��1����Ϊ�������һ������
	p->data.h =abs(end.x - p->data.x)+abs(end.y-p->data.y);//Ԥ������h�Ǹ��ݶ�X��Y��������ľ���ֵ��ӵõ���
	//ͬʱ��Ҳ������ʽ�����Ĺؼ������ڹ��ۺ�����ѡȡ�أ����кܶ�ķ���
	p->data.f =p->data.g+p->data.h;//������ֵh��g�������õ����ڵ������ֵf

	return 1;//�ɹ�����

}

int Astack::push(const point & start,const point & end,const point & n,Astack *F)//FΪ���ڵ�Ĭ��Ϊ�գ���ֻ��ϰ������//����ͷ���֮��
{
	Astack * p  = (Astack *)malloc(sizeof(Astack));//����һ���ṹ��ռ�
	Astack *q = NULL;
	p->data.x = n.x;//��������ֵ
	p->data.y = n.y;
	conpute_F(start,end,p,F);//���ݸ��ڵ�F����p�ڵ�����Ϊn.x��n.y��Fֵ
	p->futher = F;//��ָ���ڵ㣬��һ��ǳ���Ҫ����Ҫ����Ҫ
	if (next==NULL)//������ʹ��ǰ�巨�������������
	{
		next = p;
		p->next = NULL;
	}
	else
	{
		q = next;
		next = p;
		p->next = q;
	}

	return 1;//�ɹ�����

}

Astack *Astack::find_point(const point & n)
{
	Astack * p = next;
	while (p)//ѭ��һֱ��ջ�����
	{
		if (p->data.x==n.x&&p->data.y==n.y)//�����ȣ��ʹ���
		{
			return p;//���ز�ѯ����1,����ջ�д����������Ľڵ�
		}
		p = p->next;
	}
	return NULL;//���ز�ѯ����0������������nΪ����Ľڵ�
}

Astack *Astack::get_Fmin()
{
	int f = 32500;//����һ��������������f����ջ�У�ֻҪ����С���ͼ�¼ջ�е��Ǹ��ڵ��λ��
	Astack * p = next,*q = NULL ;
	while (p)
	{
		if (p->data.f<=f)
		{
			f = p->data.f;
			q= p;
		}
		p = p->next;
	}
	return q;//�����ҵ��Ľڵ�ĵ�ַ
}

int Astack::delete_point(Astack *n)//����Ҫɾ���Ľڵ��ַ
{
	int index = 0;
	Astack * p = next,*q = next;
	if (next->next==NULL)//ֻ��һ���ڵ�ʱ
	{
		next = NULL;//��ջ�ÿ�
		return 0;//ջ����
	}
	if (p->data.x==n->data.x&&p->data.y==n->data.y)//��һ���ڵ����Ҫɾ���Ľڵ�
	{
		next = next->next;//ֱ��ָ��ڶ����ڵ�
		return 1;
	}
	p = p->next;//pָ����һ���ڵ㣬����ʱq��ָ��p��

	while (p)
	{
		if (p->data.x==n->data.x&&p->data.y==n->data.y)//����
		{
			q->next = p->next;//ʹ��qֱ��ָ��p����һ���ڵ㣬�ﵽɾ����Ŀ��
			return index;//����ɾ����λ��
		}
		q = p;
		p = p->next;
	}
	return -1;//���ش����б��в���������ڵ�
}

point Astack::next_point(const point & m,int index)
{
	point n;
	switch (index)
	{
	case 0: {n.x = m.x,n.y = m.y+1;break;}//��
	case 1: {n.x = m.x+1,n.y = m.y;break;}//��
	case 2: {n.x = m.x-1,n.y = m.y;break;}//��
	case 3: {n.x = m.x,n.y = m.y-1;break;}//��
	}

	return n;	//�������ɵĽڵ�
}

//ɨ�����·��
int scan(AStarMap & A_MAP,Astack & open,Astack & close)
{
	open.push(A_MAP.start,A_MAP.end,A_MAP.start);//����ʼ�ڵ�ѹ�뿪���б�
	A_MAP.MAP[A_MAP.start.x][A_MAP.start.y] = 0;
	A_MAP.MAP[A_MAP.end.x][A_MAP.end.y] = 0;
	Astack * p  = open.get_Fmin(),*q = NULL;//�õ�open�б���Fֵ��͵Ľڵ�
	point n;
	while (true)//������ѭ������·��
	{
		if (open.find_point(A_MAP.end)||open.next==NULL)//��������յ��ڿ����б��ʱ���ҵ������·��
		{
			show_map(A_MAP,open,close);//��ʾ
			if (open.next==NULL)//�������б�Ϊ��ʱ������û��·�����Ե����յ�
			{
				printf("��ͼ���ɵ���\n");
			}
			getchar();
			return 1;
		}
		for (int x = 0;x<4;x++)//�ֱ�ɨ���ĸ�����
		{   
			n.x =p->data.x;
			n.y =p->data.y;
			n= open.next_point(n,x);//����xָʾ�ķ���õ���һ��ɨ��������
			if (A_MAP.MAP[n.x][n.y]==0&&!open.find_point(n)&&!close.find_point(n))//��ǰ����n���ڿ����б��ر��б���Ϊ0
			{
				open.push(A_MAP.start,A_MAP.end,n,p);//���뿪���б�
			}
		}
		n.x = p->data.x;//��n�����껹ԭΪ���ڵ�
		n.y = p->data.y;
		close.push(A_MAP.start,A_MAP.end,n);//�����ڵ���뵽�ر��б���
		open.delete_point(p);//�ڿ����б�ɾ�����ڵ�
		p  = open.get_Fmin();//���µõ�open�б���Fֵ��͵Ľڵ�
	}

}

void show_map(AStarMap & A_MAP,Astack & open,Astack & close)//��ʾ��ͼ�ĺ���
{

	if (A_MAP.map_lenx>20||A_MAP.map_leny>20)//���Թ���ͼ���д���20ʱ������Ļ�ߴ�Ӵ�Ϊ150*150�Ŀ���̨����
	{
		system("mode con cols=150 lines=150");
	}
	printf("��ǰ��ʼ���Ϊ��%d,%d  �յ�Ϊ:%d,%d\n�ڵ�ͼ�С�һ���Ŵ���·��,��*���Ŵ����ڵ�ͼɨ������з��ʹ��Ľڵ�\n����������ͨ��������������ǽ��\n", A_MAP.start.x, A_MAP.start.y, A_MAP.end.x, A_MAP.end.y);
	Astack * p =open.find_point(A_MAP.end);//�õ������յ�����Ľڵ㣬ʹ����ȥͨ��futherָ�뷴�ű���֮ǰ�Ľڵ㣬һֱ����㣬�͵õ���·��
	Astack * k = open.next;
	while (k)//�������б���ڵĽڵ������������MAP�и�ֵ5����ʾ���ʹ�������
	{
		A_MAP.MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	k = close.next;
	while (k)//���ر��б���ڵĽڵ������������MAP�и�ֵ5����ʾ���ʹ�������
	{
		A_MAP.MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	while (p)///�������ڵ�ͨ�����ϱ���futherָ�뵽��㣬���нڵ����������MAP�б�ȫ����ֵ2����ʾ������·��
	{
		A_MAP.MAP[p->data.x][p->data.y] = 2;
		p = p->futher;
	}
	A_MAP.MAP[A_MAP.start.x][A_MAP.start.y] = 10;//����������յ�
	A_MAP.MAP[A_MAP.end.x][A_MAP.end.y] = 11;
	for (int x = 0 ;x<A_MAP.map_lenx;x++)//ѭ�������ͼ
	{
		for (int y = 0 ; y<A_MAP.map_leny;y++)
		{
			switch (A_MAP.MAP[x][y])
			{
			case  0:{printf("��");break;}
			case  1:{printf("��");break;}
			case  2:{printf("һ");break;}
			case  5:{printf(" *");break;}
			case  10:{printf("��");break;}
			case  11:{printf("��");break;}
			}
		}
		printf("\n");
	}

}