#include "StdAfx.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "AStarSimple.h"

int **MAP; //地图二级指针，相当于二维数组的数组名，用它来动态申请地图空间
int map_lenx = 20,map_leny =20; //存放动态地图的行数和列数，默认是20*20的地图
struct point start,end;
Astack open,close;

void init_map()//初始化地图默认生成20*20的地图，当map_lenx和map_leny值变化时，地图大小也会变
{ 
	int t = 0;//用来生成随机数
	int x,y;
	MAP = (int **)malloc(sizeof(int *)*map_lenx);//动态申请map_lenx个一维数组，并赋值给MAP
	for (x = 0 ; x<map_lenx;x++)//对于每个一维数组都要申请map_leny个内存空间
	{
		MAP[x] = (int *)malloc(sizeof(int )*map_leny);
	}
	for ( x=  0 ;x<map_lenx;x++)//使用双循环对申请的动态二维数组赋值
	{
		for ( y = 0 ; y<map_leny ; y++)
		{	
			if (y==0||y==map_leny-1)//第0列和最后一列永远等于1，因为是墙壁
			{
				MAP[x][y] = 1;
				continue;
			}
			//每次都会重置srand(),并且循环调用,造成随机数据重复,将种子移到main()函数里面
			//srand((unsigned)time(NULL)+rand());//置随机种子,不然生成的地图很多时候是一样的
			t = rand()%200;//得到一个200以内的数
			if (t>40)//当t大于40时 = 0，否则 = 1，这样做是为了使可通行的空间多一些，不然太容易形成没通路的地图
			{
				MAP[x][y] = 0;
			}
			else
			{
				MAP[x][y]  = 1;
			}
		}
	}
	for (x= 0 ;x<map_leny;x++)//对地图的第零行和最后一行置1，因为是墙壁
	{
		MAP[0][x] = 1;
		MAP[map_lenx-1][x] = 1;
	}
}

Astack::Astack(void)
{
	next = NULL;
	futher = NULL;
}

Astack::~Astack(void)
{
}

int Astack::conpute_F(Astack * futher,Astack *p)
{
	if (p->data.x==start.x&&p->data.y==start.y||futher==NULL)//如果父亲节点为空，或当前节点为起点
	{
		p->data.g = 0;
		p->data.h = 0;//将f，g值置0，而h值得话，因为永远不会使用到，所以是什么值不所谓
		p->data.f =0;
		return 1;
	}
	p->data.g = futher->data.g+1;//当前节点的g值总比父节点的g值大1，因为他们相距一个距离
	p->data.h =abs(end.x - p->data.x)+abs(end.y-p->data.y);//预估代价h是根据对X，Y坐标相减的绝对值相加得到的
	//同时这也是启发式搜索的关键，对于估价函数的选取呢，还有很多的方法
	p->data.f =p->data.g+p->data.h;//将两个值h，g加起来得到本节点的评估值f

	return 1;//成功返回

}

int Astack::push(point n,Astack *F)//F为父节点默认为空，这只是习惯问题//插入头结点之后
{
	Astack * p  = (Astack *)malloc(sizeof(Astack));//申请一个结构体空间
	Astack *q = NULL;
	p->data.x = n.x;//加入坐标值
	p->data.y = n.y;
	conpute_F(F,p);//根据父节点F计算p节点坐标为n.x和n.y的F值
	p->futher = F;//反指父节点，这一点非常重要，重要，重要
	if (next==NULL)//下面是使用前插法进行链表的连接
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

	return 1;//成功返回

}

Astack *Astack::find_point(point n)
{
	Astack * p = next;
	while (p)//循环一直到栈的最后
	{
		if (p->data.x==n.x&&p->data.y==n.y)//如果相等，就存在
		{
			return p;//返回查询代码1,代表栈中存在了这样的节点
		}
		p = p->next;
	}
	return NULL;//返回查询代码0，代表不存在以n为坐标的节点
}

Astack *Astack::get_Fmin()
{
	int f = 32500;//设置一个极大数，当作f，在栈中，只要比他小，就记录栈中的那个节点的位置
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
	return q;//返回找到的节点的地址
}

int Astack::delete_point(Astack *n)//传入要删除的节点地址
{
	int index = 0;
	Astack * p = next,*q = next;
	if (next->next==NULL)//只有一个节点时
	{
		next = NULL;//将栈置空
		return 0;//栈空了
	}
	if (p->data.x==n->data.x&&p->data.y==n->data.y)//第一个节点就是要删除的节点
	{
		next = next->next;//直接指向第二个节点
		return 1;
	}
	p = p->next;//p指向下一个节点，而此时q是指向p的

	while (p)
	{
		if (p->data.x==n->data.x&&p->data.y==n->data.y)//存在
		{
			q->next = p->next;//使用q直接指向p的下一个节点，达到删除的目的
			return index;//返回删除的位置
		}
		q = p;
		p = p->next;
	}
	return -1;//返回错误，列表中不存在这个节点
}

point Astack::next_point(point m,int index)
{
	point n;
	switch (index)
	{
	case 0: {n.x = m.x,n.y = m.y+1;break;}//东
	case 1: {n.x = m.x+1,n.y = m.y;break;}//南
	case 2:{ n.x = m.x-1,n.y = m.y;break;}//西
	case 3: {n.x = m.x,n.y = m.y-1;break;}//北
	}

	return n;	//返回生成的节点
}

//扫描最短路径
int scan()
{
	open.push(start);//将开始节点压入开启列表
	MAP[start.x][start.y] = 0;
	MAP[end.x][end.y] = 0;
	Astack * p  = open.get_Fmin(),*q = NULL;//得到open列表中F值最低的节点
	point n;
	while (true)//进入死循环查找路径
	{
		if (open.find_point(end)||open.next==NULL)//如果发现终点在开启列表的时候，找到了最短路径
		{
			show_map();//显示
			if (open.next==NULL)//当开启列表为空时，代表没有路径可以到达终点
			{
				printf("地图不可到达\n");
			}
			getchar();
			return 1;
		}
		for (int x = 0;x<4;x++)//分别扫描四个方向
		{   
			n.x =p->data.x;
			n.y =p->data.y;
			n= open.next_point(n,x);//根据x指示的方向得到下一个扫描点的坐标
			if (MAP[n.x][n.y]==0&&!open.find_point(n)&&!close.find_point(n))//当前坐标n不在开启列表，关闭列表，且为0
			{
				open.push(n,p);//加入开启列表
			}
		}
		n.x = p->data.x;//将n的坐标还原为父节点
		n.y = p->data.y;
		close.push(n);//将父节点加入到关闭列表中
		open.delete_point(p);//在开启列表删除父节点
		p  = open.get_Fmin();//重新得到open列表中F值最低的节点
	}

}

void show_map()//显示地图的函数
{

	if (map_lenx>20||map_leny>20)//当迷宫地图行列大于20时，将屏幕尺寸加大为150*150的控制台窗口
	{
		system("mode con cols=150 lines=150");
	}
	printf("当前开始起点为：%d,%d  终点为:%d,%d\n在地图中“一”号代表路径,“*”号代表在地图扫描过程中访问过的节点\n“□”代表通道，“■”代表墙壁\n",start.x,start.y,end.x,end.y);
	Astack * p =open.find_point(end);//得到含有终点坐标的节点，使用它去通过futher指针反着遍历之前的节点，一直到起点，就得到了路径
	Astack * k = open.next;
	while (k)//将开启列表存在的节点包含的坐标在MAP中赋值5，表示访问过的坐标
	{
		MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	k = close.next;
	while (k)//将关闭列表存在的节点包含的坐标在MAP中赋值5，表示访问过的坐标
	{
		MAP[k->data.x][k->data.y] = 5;
		k = k->next;
	}
	while (p)///将结束节点通过不断遍历futher指针到起点，所有节点包含的坐在MAP中标全部赋值2，表示他们是路径
	{
		MAP[p->data.x][p->data.y] = 2;
		p = p->futher;
	}
	MAP[start.x][start.y] = 10;//特殊标记起点终点
	MAP[end.x][end.y] = 11;
	for (int x = 0 ;x<map_lenx;x++)//循环输出地图
	{
		for (int y = 0 ; y<map_leny;y++)
		{
			switch (MAP[x][y])
			{
			case  0:{printf("□");break;}
			case  1:{printf("■");break;}
			case  2:{printf("一");break;}
			case  5:{printf(" *");break;}
			case  10:{printf("起");break;}
			case  11:{printf("终");break;}
			}
		}
		printf("\n");
	}

}