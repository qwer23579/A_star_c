#include "StdAfx.h"
#include <algorithm>
#include "AStarSimple.h"

Astack::Astack(void)
{
	head = NULL;
}

Astack::~Astack(void)
{
	node * tempA = NULL;
#ifdef TESTMODEL
	cout<<"释放"<<endl;
#endif
	while(head)
	{
		tempA = head;
		head = head->next;
	#ifdef TESTMODEL
		cout<<tempA -> x<<","<<tempA->y<<endl;
	#endif
		delete tempA;		
	}
}
//只计算上下左右的方案
int Astack::conpute_F(const point & start,const point & end,node * p,node * futher)
{
	if (p->x==start.x && p->y==start.y||futher==NULL)//如果父亲节点为空，或当前节点为起点
	{
		p->g = 0;
		p->h = 0;//将f，g值置0，而h值得话，因为永远不会使用到，所以是什么值不所谓
		p->f = 0;
		return 1;//返回值问题
	}
	int jug = (abs(p->x - futher->x) + abs(p->y - futher->y)) == 2 ? TiltV : VertV;
	p->g = futher->g + jug;//当前节点的g值总比父节点的g值大G，因为他们相距一个距离
	int diag = std::min(abs(end.x - p->x),abs(end.y - p->y));
	int stra = abs(end.x - p->x) + abs(end.y - p->y);
	p->h =TiltV*diag + VertV*(stra - 2 * diag);//预估代价h是根据对X，Y坐标相减的绝对值相加得到的
	//同时这也是启发式搜索的关键，对于估价函数的选取呢，还有很多的方法
	p->f =p->g + p->h;//将两个值h，g加起来得到本节点的评估值f

	return p->f;//成功返回

}

int Astack::push(const point & start,const point & end,const point & point_n,node *F)//F为父节点默认为空，这只是习惯问题//插入头结点之后
{
	//Astack * p  = (Astack *)malloc(sizeof(Astack));//申请一个结构体空间
	node * p  = new node;
	node * q = NULL;

	p-> next = NULL;
	p-> futher = NULL;
	p-> x = point_n.x;//加入坐标值
	p-> y = point_n.y;
	conpute_F(start,end,p,F);//根据父节点F计算p节点坐标为n.x和n.y的F值
	p->futher = F;//反指父节点，这一点非常重要，重要，重要
	if (head==NULL)//下面是使用前插法进行链表的连接
	{
		head = p;
	}
	else
	{
		q = head;
		head = p;
		p->next = q;
	}

	return 1;//成功返回

}
int Astack::push(node *node_p)//将一个已有节点加入栈中
{
	node *q = NULL;
	node_p->next=NULL;
	if (head==NULL)//下面是使用前插法进行链表的连接
	{
		head = node_p;
		node_p->next = NULL;
	}
	else
	{
		q = head;
		head = node_p;
		node_p->next = q;
	}

	return 1;//成功返回
}
node * Astack::find_point(const point & point_n) const
{
#ifdef FindTest
	int count = 0;
	std::ofstream outFile;
	outFile.open("data.txt");
	outFile<<"进入Find查找《《《"<<endl;
	cout<<"进入Find查找《《《"<<endl;
#endif
	node * p = head;
	while (p != NULL)//循环一直到栈的最后
	{
#ifdef FindTest
		count++;
		if (count<200)
		{
			outFile<<p->x<<"\t"<<p->y<<"\t"<<p->f<<endl;
		}
#endif
		if (p->x==point_n.x && p->y==point_n.y)//如果相等，就存在
		{
#ifdef FindTest
			cout<<"退出Find查找》》》p"<<endl;
			outFile<<"退出Find查找》》》p"<<endl;
#endif
			return p;//返回查询代码1,代表栈中存在了这样的节点
		}
		p = p->next;
	}
#ifdef FindTest
	outFile<<"退出Find查找》》》0"<<endl;
	cout<<"退出Find查找》》》0"<<endl;
#endif
	return NULL;//返回查询代码0，代表不存在以n为坐标的节点
}

node *Astack::get_Fmin()
{
	int f = 32500;//设置一个极大数，当作f，在栈中，只要比他小，就记录栈中的那个节点的位置
	node * p = head , *q = NULL ;
	while (p)
	{
#ifdef TESTMODEL
		//cout<<p->x<<","<<p->y<<"min"<<endl;
#endif
		if (p->f <= f)
		{
			f = p->f;
			q = p;
		}
		p = p->next;
	}
	return q;//返回找到的节点的地址
}

int Astack::delete_point(node *node_p)//传入要删除的节点地址
{
	//int index = 0;
	node *tempA = head;//wang：临时变量
	node * p = head;//
	if (head->next==NULL)//只有一个节点时
	{	
		//p = NULL;//极其错误！！！！！！！！！！！！！！！！
		head = NULL;
		return 0;//栈空了
	}
	//wang: 保证要删除的点的前节点已知
	if (head->x==node_p->x && head->y==node_p->y)//第一个节点就是要删除的节点
	{
		head = head->next;
		tempA->next = NULL;
		//delete tempA;//wang:释放内存
		return 1;
	}
	p = p->next;//p指向下一个节点，而此时q\ tempA是指向p的

	while (p)
	{
		if (p->x==node_p->x && p->y==node_p->y)//存在
		{
			tempA->next = p->next;//使用tempA直接指向p的下一个节点，达到删除的目的
			//delete p;
			p->next = NULL;
			return 1;//返回删除的位置
		}
		tempA = p;
		p = p->next;
	}
	return -1;//返回错误，列表中不存在这个节点
}

point Astack::next_point(const point & point_n,int index)
{
	point near_n;
	switch (index)
	{
		case 0: {near_n.x = point_n.x  ,near_n.y = point_n.y+1;break;}//东
		case 1: {near_n.x = point_n.x+1,near_n.y = point_n.y  ;break;}//南
		case 2: {near_n.x = point_n.x-1,near_n.y = point_n.y  ;break;}//wang:北
		case 3: {near_n.x = point_n.x  ,near_n.y = point_n.y-1;break;}//wang:西
		case 4: {near_n.x = point_n.x+1,near_n.y = point_n.y+1;break;}//东南
		case 5: {near_n.x = point_n.x-1,near_n.y = point_n.y+1;break;}//东北
		case 6: {near_n.x = point_n.x+1,near_n.y = point_n.y-1;break;}//西南
		case 7: {near_n.x = point_n.x-1,near_n.y = point_n.y-1;break;}//西北
	}
	return near_n;	//返回生成的节点
}

//扫描最短路径
int scan(AStarMap & A_map,Astack & open,Astack & close)
{
	//system("mode con cols=150 lines=150");
	open.push(A_map.start,A_map.end,A_map.start);//将开始节点压入开启列表
	A_map.map[A_map.start.x][A_map.start.y] = 0;
	A_map.map[A_map.end.x][A_map.end.y] = 0;
	node * p  = open.get_Fmin(),*q = NULL;//得到open列表中F值最低的节点
	point n;
	node nodenew;
	node *nodeold = NULL;
	nodenew.next = NULL;
	while (1)//进入死循环查找路径
	{
#ifdef TESTMODEL
		cout<<"       "<<"父节点"<<p->x<<","<<p->y<<"进入新的判断"<<endl;
#endif
		if (open.find_point(A_map.end)||open.head==NULL)//如果发现终点在开启列表的时候，找到了最短路径
		{
			printf("\n计算结束\n");//Wang
			show_map(A_map,open,close);//显示
			if (open.head==NULL)//当开启列表为空时，代表没有路径可以到达终点
			{
				printf("地图不可到达\n");//Wang：若有且只有一条路径呢？
			}
			getchar();
			return 1;
		}
		for (int i = 0;i<8;i++)//分别扫描四个方向
		{   
#ifdef TESTMODEL
			cout<<"i="<<i<<endl;
#endif
			n.x =p->x;
			n.y =p->y;
			n = open.next_point(n,i);//根据x指示的方向得到下一个扫描点的坐标
			if (i >= 4 && ((A_map.map[n.x][p->y] == Obstacle) || (A_map.map[p->x][n.y] == Obstacle)))
			{
			#ifdef TESTMODEL
				printf("跳过节点：（%d,%d)，父节点为（%d,%d）\n",n.x,n.y,p->x,p->y);
				//show_map(A_map,open,close);//显示
			#endif
				continue;//如果是斜方向移动, 不能从两个障碍对角穿过去
			}
#ifdef TESTMODEL
			cout<<"考察点"<<n.x<<","<<n.y<<endl;
#endif
			if (A_map.map[n.x][n.y]< Obstacle && !close.find_point(n))
			{
				if(!open.find_point(n))//当前坐标n不在开启列表，关闭列表，且为0
				{
					open.push(A_map.start,A_map.end,n,p);//加入开启列表
				#ifdef TESTMODEL
					cout<<n.x<<","<<n.y<<"加入open"<<endl;
				#endif
				}
				//重新计算f值，并看是否需要更新父节点
				else
				{
					nodeold = open.find_point(n);
					nodenew.x = n.x ;
					nodenew.y = n.y;
					open.conpute_F(A_map.start,A_map.end,&nodenew,p);//根据父节点F计算p节点坐标为n.x和n.y的F值
					if (nodenew.f < nodeold->f)
					{
						nodeold->g = nodenew.g;
						nodeold->h = nodenew.h;
						nodeold->f = nodenew.f;
						nodeold->futher = p;
					#ifdef TESTMODEL
						cout<<n.x<<","<<n.y<<"被重新评估"<<endl;
					#endif
					}
				}
			}
		}
		n.x = p->x;//将n的坐标还原为父节点
		n.y = p->y;
		open.delete_point(p);//在开启列表删除父节点
		close.push(p);//将父节点加入到关闭列表中
	#ifdef TESTMODEL
		cout<<p->x<<","<<p->y<<"放入close列表"<<endl;
	#endif
		p = open.get_Fmin();//重新得到open列表中F值最低的节点
	}
}

void show_map(AStarMap & A_map,Astack & open,Astack & close)//显示地图的函数
{
	if (A_map.map_lenx>20||A_map.map_leny>20)//当迷宫地图行列大于20时，将屏幕尺寸加大为150*150的控制台窗口
	{
		system("mode con cols=150 lines=150");
	}
	printf("当前开始起点为：%d,%d  终点为:%d,%d\n在地图中“一”号代表路径,“*”号代表在地图扫描过程中访问过的节点\n“□”代表通道，“■”代表墙壁\n", A_map.start.x, A_map.start.y, A_map.end.x, A_map.end.y);
	node * p = open.find_point(A_map.end);//得到含有终点坐标的节点，使用它去通过futher指针反着遍历之前的节点，一直到起点，就得到了路径
	node * k = open.head;
	while (k)//将开启列表存在的节点包含的坐标在map中赋值5，表示访问过的坐标
	{
		A_map.map[k->x][k->y] = 5;
		k = k->next;
	}
	k = close.head;
	while (k)//将关闭列表存在的节点包含的坐标在map中赋值5，表示访问过的坐标
	{
		A_map.map[k->x][k->y] = 6;
		k = k->next;
	}
	while (p)///将结束节点通过不断遍历futher指针到起点，所有节点包含的坐在map中标全部赋值2，表示他们是路径
	{
		A_map.map[p->x][p->y] = 2;
		p = p->futher;
	}
	A_map.map[A_map.start.x][A_map.start.y] = 10;//特殊标记起点终点
	A_map.map[A_map.end.x][A_map.end.y] = 11;
	for (int x = 0 ;x<A_map.map_lenx;x++)//循环输出地图
	{
		for (int y = 0 ; y<A_map.map_leny;y++)
		{
			switch (A_map.map[x][y])
			{
			case  0:{printf("□");break;}
			case  2:{printf("一");break;}
			case  5:{printf(" *");break;}
			case  6:{printf(" @");break;}
			case  10:{printf("起");break;}
			case  11:{printf("终");break;}
			case  Obstacle:{printf("■");break;}
			}
		}
		printf("\n");
	}

}
