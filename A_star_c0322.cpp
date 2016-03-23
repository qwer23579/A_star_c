// A_star_c0322.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

// ������ʹ��A*�㷨��д����VSϵ�п���ƽ̨��д�����Լ���VCϵ�п��������������TCϵ�п���ƽ̨������
	//A*�㷨��һ�־�̬·�������Ч���������·�����㷨
	//����˼���ǣ�����ʽ������������ĵ��ǹ��ۺ���F������ֵ�� = G�����ڵ㵽�Լ��Ĵ��ۣ�+H���Լ����յ�����۾��룩
	//ѧϰ��A*�㷨Ҳ��ͬʱѧϰ�˵Ͽ���˹���㷨���������ݽṹ�α��ϵķ���������Ϊ��˹���㷨��A*�㷨��һ���������
	//�����������˹���㷨û������ʽ������Ҳ���ǹ��ۺ���F= G+H�е�H��Զ����0�����������˹���㷨
#include "stdio.h"
#include "time.h"
#include "stdlib.h"

void show_map();

int **MAP; //��ͼ����ָ�룬�൱�ڶ�ά���������������������̬�����ͼ�ռ�
int map_lenx = 20,map_leny =20; //��Ŷ�̬��ͼ��������������Ĭ����20*20�ĵ�ͼ

//��ʼ����ͼ
void init_map()//��ʼ����ͼĬ������20*20�ĵ�ͼ����map_lenx��map_lenyֵ�仯ʱ����ͼ��СҲ���
{ 
	int t = 0;//�������������
	int x,y;
	MAP = (int **)malloc(sizeof(int *)*map_lenx);//��̬����map_lenx��һά���飬����ֵ��MAP
	for (x = 0 ; x<map_lenx;x++)//����ÿ��һά���鶼Ҫ����map_leny���ڴ�ռ�
	{
		MAP[x] = (int *)malloc(sizeof(int )*map_leny);
	}
	for ( x=  0 ;x<map_lenx;x++)//ʹ��˫ѭ��������Ķ�̬��ά���鸳ֵ
	{
		for ( y = 0 ; y<map_leny ; y++)
		{	
			if (y==0||y==map_leny-1)//��0�к����һ����Զ����1����Ϊ��ǽ��
			{
				MAP[x][y] = 1;
				continue;
			}
			//ÿ�ζ�������srand(),����ѭ������,�����������ظ�,�������Ƶ�main()��������
			//srand((unsigned)time(NULL)+rand());//���������,��Ȼ���ɵĵ�ͼ�ܶ�ʱ����һ����
			t = rand()%200;//�õ�һ��200���ڵ���
			if (t>40)//��t����40ʱ = 0������ = 1����������Ϊ��ʹ��ͨ�еĿռ��һЩ����Ȼ̫�����γ�ûͨ·�ĵ�ͼ
			{
				MAP[x][y] = 0;
			}
			else
			{
				MAP[x][y]  = 1;
			}
		}
	}
	for (x= 0 ;x<map_leny;x++)//�Ե�ͼ�ĵ����к����һ����1����Ϊ��ǽ��
	{
		MAP[0][x] = 1;
		MAP[map_lenx-1][x] = 1;
	}
}

struct node//�����ڵ�
{
	int  x,y;//��¼�ڵ�ͼ�е�xy����
	int f,g,h;//�ڵ�����ֵf = ���ڵ㵽��ǰ�ڵ�Ĵ���g+��ǰ�ڵ㵽�յ��Ԥ������h����f=g+h
};

struct point
{
	int x,y;//����
}start,end;//�ڵ�����ṹ�壬ע�⣬�ڴ˴��������˿�ʼstart��end

struct  stack//��ʾ�������ڽṹ�嶨�������������open�б���close�б��ں����п�����Ҫ����
{
	node data;//ջ��ÿһ�����ݽڵ㣬������ݽڵ��¼���Լ������������ֵf��Ԥ��ֵh�������Ĵ���g
	stack *next;//ָ����һ���ڵ��ָ��
	stack *futher;//ָ�򸸽ڵ㣬����ǳ���Ҫ����Ϊ��ɨ���յ��ʱ��ͨ����ͣ�����ѯ���ڵ�Ϳ��Եõ������·��

	//��ʼ��ջ
	int init()//��ʼ��ջ
	{
		next = NULL;
		futher = NULL;
	}
	//����һ���ڵ��Fֵ
	int conpute_F(stack * futher,stack *p)//futherΪp�ĸ��׽ڵ�
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
	//��һ���ڵ����ջ��
	int push(point n,stack *F = NULL)//FΪ���ڵ�Ĭ��Ϊ�գ���ֻ��ϰ�����⣬
	{
		stack * p  = (stack *)malloc(sizeof(stack));//����һ���ṹ��ռ�
		stack *q = NULL;
		p->data.x = n.x;//��������ֵ
		p->data.y = n.y;
		conpute_F(F,p);//���ݸ��ڵ�F����p�ڵ�����Ϊn.x��n.y��Fֵ
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
	//����ջ���Ƿ������nΪ����Ľڵ�
	stack * find_point(point n)
	{
		stack * p = next;
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

	//�õ�һ��f��С�Ľڵ㣬����������ڵ�ĵ�ַ
	stack *get_Fmin()
	{
		int f = 32500;//����һ��������������f����ջ�У�ֻҪ����С���ͼ�¼ջ�е��Ǹ��ڵ��λ��
		stack * p = next,*q = NULL ;
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
	//ɾ��ջ��һ���ڵ�
	int delete_point(stack *n)//����Ҫɾ���Ľڵ��ַ
	{
		int index = 0;
		stack * p = next,*q = next;
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
	//ͨ����ǰ����m����index��ָʾ�ķ��������һ���ڵ�����
	point next_point(point m,int index = 0)
	{
		point n;
		switch (index)
		{
		case 0: {n.x = m.x,n.y = m.y+1;break;}//��
		case 1: {n.x = m.x+1,n.y = m.y;break;}//��
		case 2:{ n.x = m.x-1,n.y = m.y;break;}//��
		case 3: {n.x = m.x,n.y = m.y-1;break;}//��
		}

		return n;	//�������ɵĽڵ�
	}

	//ɨ�����·��
	int scan()
	{
		open.push(start);//����ʼ�ڵ�ѹ�뿪���б�
		MAP[start.x][start.y] = 0;
		MAP[end.x][end.y] = 0;
		stack * p  = get_Fmin(),*q = NULL;//�õ�open�б���Fֵ��͵Ľڵ�
		point n;
		while (true)//������ѭ������·��
		{
			if (find_point(end)||open.next==NULL)//��������յ��ڿ����б��ʱ���ҵ������·��
			{
				show_map();//��ʾ
				if (open.next==NULL)//�������б�Ϊ��ʱ������û��·�����Ե����յ�
				{
					printf("��ͼ���ɵ���\n");
				}
				getchar();
				return 1;
			}
			for (int x = 0;x<4;x++)//�ֱ�ɨ���ĸ�����
			{   n.x =p->data.x;
			n.y =p->data.y;
			n= next_point(n,x);//����xָʾ�ķ���õ���һ��ɨ��������
			if (MAP[n.x][n.y]==0&&!find_point(n)&&!close.find_point(n))//��ǰ����n���ڿ����б��ر��б���Ϊ0
			{
				open.push(n,p);//���뿪���б�
			}
			}
			n.x = p->data.x;//��n�����껹ԭΪ���ڵ�
			n.y = p->data.y;
			close.push(n);//�����ڵ���뵽�ر��б���
			delete_point(p);//�ڿ����б�ɾ�����ڵ�
			p  = get_Fmin();//���µõ�open�б���Fֵ��͵Ľڵ�
		}

	}

}open,close;//���뿪���б�͹ر��б�

void show_map()//��ʾ��ͼ�ĺ���
{

	if (map_lenx>20||map_leny>20)//���Թ���ͼ���д���20ʱ������Ļ�ߴ�Ӵ�Ϊ150*150�Ŀ���̨����
	{
		system("mode con cols=150 lines=150");
	}
	printf("��ǰ��ʼ���Ϊ��%d,%d  �յ�Ϊ:%d,%d\n�ڵ�ͼ�С�һ���Ŵ���·��,��*���Ŵ����ڵ�ͼɨ������з��ʹ��Ľڵ�\n����������ͨ��������������ǽ��\n",start.x,start.y,end.x,end.y);
	stack * p =open.find_point(end);//�õ������յ�����Ľڵ㣬ʹ����ȥͨ��futherָ�뷴�ű���֮ǰ�Ľڵ㣬һֱ����㣬�͵õ���·��
	stack * k = open.next;
	while (k)//�������б���ڵĽڵ������������MAP�и�ֵ5����ʾ���ʹ�������
	{
		MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	k = close.next;
	while (k)//���ر��б���ڵĽڵ������������MAP�и�ֵ5����ʾ���ʹ�������
	{
		MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	while (p)///�������ڵ�ͨ�����ϱ���futherָ�뵽��㣬���нڵ����������MAP�б�ȫ����ֵ2����ʾ������·��
	{
		MAP[p->data.x][p->data.y] = 2;
		p = p->futher;
	}
	MAP[start.x][start.y] = 10;//����������յ�
	MAP[end.x][end.y] = 11;
	for (int x = 0 ;x<map_lenx;x++)//ѭ�������ͼ
	{
		for (int y = 0 ; y<map_leny;y++)
		{
			switch (MAP[x][y])
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

void main()
{	
	while (true)
	{
		//srand(time(NULL));
		printf("A���㷨��̬·�����·��������\n�������ͼ������������(��ͼ��Χ�����3*3-100*100��)\n");
		scanf("%d",&map_lenx);
		scanf("%d",&map_leny);
		printf("�������ͼ���x,y��(��㷶ΧX:1-%d,Y1-%d)\n",map_lenx-2,map_leny-2);
		scanf("%d,%d",&start.x);
		scanf("%d",&start.y);
		printf("�������ͼ�յ�x,y��(�յ㷶ΧX:1-%d,Y1-%d)\n",map_lenx-2,map_leny-2);
		scanf("%d",&end.x);
		scanf("%d",&end.y);
		if (start.x>map_lenx-1||start.y>map_leny-1||end.x>map_lenx-1||end.y>map_leny-1)
		{
			printf("�����յ����ڵ�ͼ�⣬�޷�Ѱ·!!!\n�����������....\n");
			getchar();
			continue;
		}
		init_map();//��ʼ����ͼ
		open.scan();//ɨ��·��
		open.next = NULL;//�ÿտ����б�͹ر��б�
		close.next = NULL;
	}
}
