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
//ֻ�����������ҵķ���
int Astack::conpute_F(const point & start,const point & end,Astack *p,Astack * futher)
{
	if (p->data.x==start.x&&p->data.y==start.y||futher==NULL)//������׽ڵ�Ϊ�գ���ǰ�ڵ�Ϊ���
	{
		p->data.g = 0;
		p->data.h = 0;//��f��gֵ��0����hֵ�û�����Ϊ��Զ����ʹ�õ���������ʲôֵ����ν
		p->data.f =0;
		return 1;//����ֵ����
	}
	int G = (abs(p->data.x - start.x) + abs(p->data.x - start.y)) == 2 ? VertV : TiltV;
	p->data.g = futher->data.g + G;//��ǰ�ڵ��gֵ�ܱȸ��ڵ��gֵ��G����Ϊ�������һ������
	p->data.h =VertV*abs(end.x - p->data.x)+VertV*abs(end.y-p->data.y);//Ԥ������h�Ǹ��ݶ�X��Y��������ľ���ֵ��ӵõ���
	//ͬʱ��Ҳ������ʽ�����Ĺؼ������ڹ��ۺ�����ѡȡ�أ����кܶ�ķ���
	p->data.f =p->data.g+p->data.h;//������ֵh��g�������õ����ڵ������ֵf

	return p->data.f;//�ɹ�����

}

int Astack::push(const point & start,const point & end,const point & point_n,Astack *F)//FΪ���ڵ�Ĭ��Ϊ�գ���ֻ��ϰ������//����ͷ���֮��
{
	//Astack * p  = (Astack *)malloc(sizeof(Astack));//����һ���ṹ��ռ�
	Astack * p  = new Astack;
	Astack *q = NULL;
	p->data.x = point_n.x;//��������ֵ
	p->data.y = point_n.y;
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

Astack *Astack::find_point(const point & point_n)
{
	Astack * p = next;
	while (p)//ѭ��һֱ��ջ�����
	{
		if (p->data.x==point_n.x&&p->data.y==point_n.y)//�����ȣ��ʹ���
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
			q = p;
		}
		p = p->next;
	}
	return q;//�����ҵ��Ľڵ�ĵ�ַ
}

int Astack::delete_point(Astack *Astack_p)//����Ҫɾ���Ľڵ��ַ
{
	int index = 0;
	Astack *tempA = next;//wang����ʱ����
	Astack * p = next;//,*q = next;
	if (p->next==NULL)//ֻ��һ���ڵ�ʱ
	{
		
		p = NULL;//��ջ�ÿ�
		//delete p;//wang
		return 0;//ջ����
	}
	//wang: ��֤Ҫɾ���ĵ��ǰ�ڵ���֪
	if (p->data.x==Astack_p->data.x&&p->data.y==Astack_p->data.y)//��һ���ڵ����Ҫɾ���Ľڵ�
	{
		next = next->next;//ֱ��ָ��ڶ����ڵ�
		//delete tempA;//wang:�ͷ��ڴ�
		return 1;
	}
	p = p->next;//pָ����һ���ڵ㣬����ʱq\ tempA��ָ��p��

	while (p)
	{
		if (p->data.x==Astack_p->data.x&&p->data.y==Astack_p->data.y)//����
		{
			tempA->next = p->next;//ʹ��qֱ��ָ��p����һ���ڵ㣬�ﵽɾ����Ŀ��
			//delete p;
			return index;//����ɾ����λ��
		}
		tempA = p;
		p = p->next;
	}
	return -1;//���ش����б��в���������ڵ�
}

point Astack::next_point(const point & point_n,int index)
{
	point near_n;
	switch (index)
	{
		case 0: {near_n.x = point_n.x  ,near_n.y = point_n.y+1;break;}//��
		case 1: {near_n.x = point_n.x+1,near_n.y = point_n.y  ;break;}//��
		case 2: {near_n.x = point_n.x-1,near_n.y = point_n.y  ;break;}//wang:��
		case 3: {near_n.x = point_n.x  ,near_n.y = point_n.y-1;break;}//wang:��
		case 4: {near_n.x = point_n.x+1,near_n.y = point_n.y+1;break;}//����
		case 5: {near_n.x = point_n.x-1,near_n.y = point_n.y+1;break;}//����
		case 6: {near_n.x = point_n.x+1,near_n.y = point_n.y-1;break;}//����
		case 7: {near_n.x = point_n.x-1,near_n.y = point_n.y-1;break;}//����

	}
	return near_n;	//�������ɵĽڵ�
}

//ɨ�����·��
int scan(AStarMap & A_map,Astack & open,Astack & close)
{
	open.push(A_map.start,A_map.end,A_map.start);//����ʼ�ڵ�ѹ�뿪���б�
	A_map.map[A_map.start.x][A_map.start.y] = 0;
	A_map.map[A_map.end.x][A_map.end.y] = 0;
	Astack * p  = open.get_Fmin(),*q = NULL;//�õ�open�б���Fֵ��͵Ľڵ�
	point n;
	while (true)//������ѭ������·��
	{
		if (open.find_point(A_map.end)||open.next==NULL)//��������յ��ڿ����б��ʱ���ҵ������·��
		{
			show_map(A_map,open,close);//��ʾ
			if (open.next==NULL)//�������б�Ϊ��ʱ������û��·�����Ե����յ�
			{
				printf("��ͼ���ɵ���\n");//Wang��������ֻ��һ��·���أ�
			}
			getchar();
			return 1;
		}
		for (int x = 0;x<8;x++)//�ֱ�ɨ���ĸ�����
		{   
			n.x =p->data.x;
			n.y =p->data.y;
			n= open.next_point(n,x);//����xָʾ�ķ���õ���һ��ɨ��������
// 			if (A_map.map[n.x][n.y]==0&&!open.find_point(n)&&!close.find_point(n))//��ǰ����n���ڿ����б��ر��б���Ϊ0
// 			{
// 				open.push(A_map.start,A_map.end,n,p);//���뿪���б�
// 			}
			if (x >= 4 && A_map.map[n.x][p->data.y]!=0 && A_map.map[p->data.x][n.y]!=0)
			{
				continue;
			}
			if (A_map.map[n.x][n.y]==0 && !close.find_point(n))
			{
				if (!open.find_point(n))//��ǰ����n���ڿ����б��ر��б���Ϊ0
				{
					open.push(A_map.start,A_map.end,n,p);//���뿪���б�
				}
// 				if (open.find_point(n))//��ǰ����n���ڿ����б��ر��б���Ϊ0
// 				{
// 					open.push(A_map.start,A_map.end,n,p);//���뿪���б�
// 				}
			}
		}
		n.x = p->data.x;//��n�����껹ԭΪ���ڵ�
		n.y = p->data.y;
		close.push(A_map.start,A_map.end,n);//�����ڵ���뵽�ر��б���
		open.delete_point(p);//�ڿ����б�ɾ�����ڵ�
		p  = open.get_Fmin();//���µõ�open�б���Fֵ��͵Ľڵ�
	}

}

void show_map(AStarMap & A_map,Astack & open,Astack & close)//��ʾ��ͼ�ĺ���
{

	if (A_map.map_lenx>20||A_map.map_leny>20)//���Թ���ͼ���д���20ʱ������Ļ�ߴ�Ӵ�Ϊ150*150�Ŀ���̨����
	{
		system("mode con cols=150 lines=150");
	}
	printf("��ǰ��ʼ���Ϊ��%d,%d  �յ�Ϊ:%d,%d\n�ڵ�ͼ�С�һ���Ŵ���·��,��*���Ŵ����ڵ�ͼɨ������з��ʹ��Ľڵ�\n����������ͨ��������������ǽ��\n", A_map.start.x, A_map.start.y, A_map.end.x, A_map.end.y);
	Astack * p =open.find_point(A_map.end);//�õ������յ�����Ľڵ㣬ʹ����ȥͨ��futherָ�뷴�ű���֮ǰ�Ľڵ㣬һֱ����㣬�͵õ���·��
	Astack * k = open.next;
	while (k)//�������б���ڵĽڵ������������map�и�ֵ5����ʾ���ʹ�������
	{
		A_map.map[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	k = close.next;
	while (k)//���ر��б���ڵĽڵ������������map�и�ֵ5����ʾ���ʹ�������
	{
		A_map.map[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	while (p)///�������ڵ�ͨ�����ϱ���futherָ�뵽��㣬���нڵ����������map�б�ȫ����ֵ2����ʾ������·��
	{
		A_map.map[p->data.x][p->data.y] = 2;
		p = p->futher;
	}
	A_map.map[A_map.start.x][A_map.start.y] = 10;//����������յ�
	A_map.map[A_map.end.x][A_map.end.y] = 11;
	for (int x = 0 ;x<A_map.map_lenx;x++)//ѭ�������ͼ
	{
		for (int y = 0 ; y<A_map.map_leny;y++)
		{
			switch (A_map.map[x][y])
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