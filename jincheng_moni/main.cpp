#include<iostream>
using namespace std;

typedef struct PCB
{
	int id;
	char name[10];
	int xtime;
	int pri;
	int state;/*0:就绪
			  1：阻塞
			  2：运行*/
	PCB* next;
}PCB;

PCB* p_run = NULL;
PCB* p_wait0 = NULL;//i/o阻塞
PCB* p_wait1 = NULL;
PCB* p_wait0_rear = NULL;
PCB* p_wait1_rear = NULL;
PCB* p_ready = NULL;
PCB* p_ready_rear = NULL;

void init();
void create();
void kill();
void time_arrive();
void susp(int a);
void wakeup();
void setpri();
void show();
int num;
void pcb_control();
int kong = 0;

int main()
{
	init();
	int a, b;
	while (1)
	{
		cout << "-------菜单-------" << endl;
		cout << endl;
		cout << " 1 创建" << endl;
		cout << " 2 撤销" << endl;
		cout << " 3 时间片到" << endl;
		cout << " 4 阻塞进程" << endl;
		cout << " 5 激活进程" << endl;
		cout << " 6 改变优先级" << endl;
		cout << " 7 显示" << endl;
		cout << " 8 退出" << endl;
		cout << endl;
		cout << "-------菜单-------" << endl;
		cin >> a;
		switch (a)
		{
		case 1:create(); break;
		case 2:kill(); break;
		case 3:time_arrive(); break;
		case 4:
			cout << "选择阻塞原因：" << endl;
			cout << "0:i/o事件导致阻塞" << endl;
			cout << "1:其他" << endl;
			cin >> b;
			susp(b);
			break;
		case 5:wakeup(); break;
		case 6:setpri(); break;
		case 7:show(); break;
		case 8:exit(0); break;
		default:break;
		}
	}
	return 0;

}

void init()
{
	PCB* p;
	cout << "输出PCB个数" << endl;
	cin >> num;
	p_ready = new PCB;
	cout << "输入id" << endl;
	cin >> p_ready->id;
	cout << "输入进程名" << endl;
	cin >> p_ready->name;
	cout << "输入运行时间" << endl;
	cin >> p_ready->xtime;
	p_ready->state = 0;
	p_ready->pri = 0;
	p_ready->next = NULL;
	p_ready_rear = p_ready;
	for (int i = 1; i < num; i++)
	{
		p = new PCB;
		cout << "输入id" << endl;
		cin >> p->id;
		cout << "输入进程名" << endl;
		cin >> p->name;
		cout << "输入运行时间" << endl;
		cin >> p->xtime;
		p->state = 0;
		p->pri = 0;
		p->next = NULL;
		p_ready_rear->next = p;
		p_ready_rear = p_ready_rear->next;
	}
	pcb_control();

}

void create()
{
	int tag = 0;
	int id;
	cout << "请输入进程id" << endl;
	cin >> id;
	PCB* p = p_ready;
	while (p != NULL)
	{
		if (id == p->id)
		{
			tag = 1;
			break;
		}
	}
	p = p_wait0;
	while (p != NULL)
	{
		if (id == p->id)
		{
			tag = 1;
			break;
		}
	}
	p = p_wait1;
	while (p != NULL)
	{
		if (id == p->id)
		{
			tag = 1;
			break;
		}
	}
	if (kong <= 0)
		tag = 1;
	if (tag == 0)
	{
		p = new PCB;
		cout << "输入进程名称" << endl;
		cin >> p->name;
		cout << "输入运行时间" << endl;
		cin >> p->xtime;
		p->state = 0;
		p->pri = 0;
		p->next = NULL;
		p_ready_rear->next = p;
		p_ready_rear = p_ready_rear->next;
	}
	else
	{
		cout << "创建失败" << endl;
	}
}

void pcb_control()//就绪转运行
{
	p_run = p_ready;
	p_ready = p_ready->next;
	if (p_ready == NULL)
	{
		p_ready = p_ready_rear = NULL;
	}
	p_run->state = 2;
	p_run->next = NULL;
}

void kill()//运行完成
{
	PCB* p = p_run;
	pcb_control();
	delete(p);
	kong++;
}

void time_arrive()//时间片到
{
	p_run->state = 0;
	p_ready_rear->next = p_run;
	p_run->next = NULL;
	p_ready_rear = p_ready_rear->next;
	pcb_control();
}

void susp(int a)//运行转阻塞
{
	if (a != 0 && a != 1)
	{
		cout << "输入错误" << endl;
		return;
	}
	p_run->state = 1;
	switch (a)
	{
	case 0:
		if (p_wait0 == NULL)
			p_wait0 = p_wait0_rear = p_run;
		else
		{
			p_wait0_rear->next = p_run;
			p_wait0_rear = p_wait0_rear->next;
		}
		p_wait0_rear->next = NULL;
		break;
	case 1:
		if (p_wait1 == NULL)
			p_wait1 = p_wait1_rear = p_run;
		else
		{
			p_wait1_rear->next = p_run;
			p_wait1_rear = p_wait1_rear->next;
		}
		p_wait1_rear->next = NULL;
		break;
	}
	pcb_control();
}

void wakeup() //阻塞转就绪
{
	int a;
	cout << "请选择唤醒进程的队列：" << endl;
	cout << "0：i/o事件导致阻塞" << endl;
	cout << "1：其他事件导致阻塞" << endl;
	cin >> a;
	switch (a)
	{
	case 0:
		if (p_wait0 == NULL)
			cout << "该队列不存在阻塞" << endl;
		else
		{
			p_wait0->state = 0;
			p_ready_rear->next = p_wait0;
			p_ready_rear = p_ready_rear->next;
			p_wait0 = p_wait0->next;
			p_ready_rear->next = NULL;
		}
		break;
	case 1:
		if (p_wait1 == NULL)
			cout << "该队列不存在阻塞" << endl;
		else
		{
			p_wait1->state = 0;
			p_ready_rear->next = p_wait1;
			p_ready_rear = p_ready_rear->next;
			p_wait1 = p_wait1->next;
			p_ready_rear->next = NULL;
		}
		break;
	default:cout << "输入错误" << endl;
	}
}

void setpri()
{
	int a;
	cout << "请输入id" << endl;
	cin >> a;
	PCB* p=p_run;
	if (a == p->id)
	{
		cout << "请输入优先数" << endl;
		cin >> p->pri;
		return;
	}
	p = p_ready;
	while (p != NULL)
	{
		if (a == p->id)
		{
			cout << "请输入优先数" << endl;
			cin >> p->pri;
			return;
		}
		else
			p = p->next;
	}
	p = p_wait0;
	while (p != NULL)
	{
		if (a == p->id)
		{
			cout << "请输入优先数" << endl;
			cin >> p->pri;
			return;
		}
		else
			p = p->next;
	}
	p = p_wait1;
	while (p != NULL)
	{
		if (a == p->id)
		{
			cout << "请输入优先数" << endl;
			cin >> p->pri;
			return;
		}
		else
			p = p->next;
	}
	cout << "输入id错误" << endl;
}

void show()
{
	PCB* p;
	cout << "---------------" << endl;
	cout << "正在运行的进程" << endl;
	cout << "ID:" << p_run->id << "NAME：" << p_run->name << "完成时间:" << p_run->xtime << "优先数：" << p_run->pri << endl;
	cout << "---------------" << endl;
	p = p_ready;
	cout << "就绪的进程" << endl;
	while (p != NULL)
	{
		cout << "ID:" << p->id << "NAME：" << p->name << "完成时间:" << p->xtime << "优先数：" << p->pri << endl;
		p = p->next;
	}
	cout << "---------------" << endl;
	p = p_wait0;
	cout << "等待i/o的进程" << endl;
	while (p != NULL)
	{
		cout << "ID:" << p->id << "NAME：" << p->name << "完成时间:" << p->xtime << "优先数：" << p->pri << endl;
		p = p->next;
	}
	cout << "---------------" << endl;
	p = p_wait1;
	cout << "其他阻塞的进程" << endl;
	while (p != NULL)
	{
		cout << "ID:" << p->id << "NAME：" << p->name << "完成时间:" << p->xtime << "优先数：" << p->pri << endl;
		p = p->next;
	}
	cout << "---------------" << endl;
}
