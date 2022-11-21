#include<iostream>
using namespace std;

#define MAX_ADDRESS 128

class area{
private:
    int size; //大小
    int first_ad; //内存首地址
    int flag; //0表示空闲 ，其他值代表作业的id
public:
    area( int size = 0,int first_ad = 0,int flag = 0)
    {
        this->size = size;
        this->first_ad = first_ad;
        this->flag  = flag;
    }

    void print()
    {
        cout<<this->first_ad<<"   "<<"\t"<<this->size<<"\t"<<this->flag<<endl;
    }
    int  compute_last_ad()
    {
        return this->size + this->first_ad - 1;
    }
    int get_size()
    {
        return this->size;
    }
    int get_first_ad()
    {
        return this->first_ad;
    }
    int get_flag()
    {
        return this->flag;
    }
    void set_size(int size)
    {
        this->size = size;
    }
    void set_first_ad(int fa)
    {
        this->first_ad = fa;
    }
    void set_flag(int flag)
    {
        this->flag = flag;
    }
};

struct work{
    int size;
    int id;
};
bool first_allocation(int *pf,int *pb,work B, area *free, area *busy,int limit);
bool best_allocation(int *pf,int *pb,work B,area *free,area *busy,int limit);
bool worst_allocation(int *pf,int *pb,work B,area *free,area *busy,int limit);
bool recycle(int *pf,int *pb,int id,area *free,area *busy);
void sort(int p, area *queue);
void sort2( int p, area* queue)
{
    for(int i  = 0 ; i < p ; i++)
        for(int j = i + 1 ; j<p  ; j++)
        {
            if(queue[i].get_size()>queue[j].get_size())
            {
                area t = queue[j];
                queue[j] = queue[i];
                queue[i] = t;
            }
        }
}
void sort3( int p, area* queue)
{
    for(int i  = 0 ; i < p ; i++)
        for(int j = i + 1 ; j<p  ; j++)
        {
            if(queue[i].get_size()<queue[j].get_size())
            {
                area t = queue[j];
                queue[j] = queue[i];
                queue[i] = t;
            }
        }
}
int main()
{
    area *free  = new area[MAX_ADDRESS];
    area *busy  = new area[MAX_ADDRESS];
    int p_free = 4;
    int p_busy = 4;
    area work1(8,0,1);
    area work2(32,30,2);
    area work3(4,80,3);
    area work4(2,10,4);
    busy[0] = work1;
    busy[1] = work2;
    busy[2] = work3;
    busy[3] = work4;
    sort(p_busy,busy);
    area free1(2,8,0);
    area free2(18,12,0);
    area free3(18,62,0);
    area free4(66,84,0);
    free[0] = free1;
    free[1] = free2;
    free[2] = free3;
    free[3] = free4;
    sort(p_free,free);
    int limit;
    cout<<"欢迎来到模拟内存管理分配回收系统"<<endl;
    cout<<"请输入你想设置的门限值(必须为数字)："<<endl;
    cin>>limit;
    int op;
    while(1){
        cout<<"请输入你的操作"<<endl;
        cout<<"1:创建作业"<<endl;
        cout<<"2:回收作业"<<endl;
        cout<<"3:输出队列"<<endl;
        cout<<"0:退出"<<endl;
        cin>>op;
        switch (op){
            case 1:
            {   int size,id;
                bool flag =true;
                work now;
                cout<<"请输入作业id:";
                cin>>id;
                for(int i=0;i<p_busy;i++)
                    if(busy[i].get_flag() == id) {
                        cout << "输入错误!"<<endl;
                        flag =false;
                        break;
                    }
                if(flag == false)
                break;
                cout<<"请输入作业大小:"<<endl;
                cin>>size;
                now.size = size;
                now.id = id;
                int choice;
                cout<<"请选择组织策略:"<<endl;
                cout<<"1:首先适应算法"<<endl;
                cout<<"2:最佳适应算法"<<endl;
                cout<<"3:最坏适应算法"<<endl;
                cin>>choice;
                switch(choice){
                    case 1:
                    {
                        bool result = first_allocation(&p_free,&p_busy,now,free,busy,limit);
                        sort(p_free,free);
                        if(result) {
                            cout << "分配成功!"<<endl;
                            break;
                        }
                        else {
                            cout << "分配失败!"<<endl;
                            break;
                        }
                    }//case1
                    case 2:
                    {
                        sort2(p_free,free);
                        bool result = best_allocation(&p_free,&p_busy,now,free,busy,limit);
                        if(result) {
                            cout << "分配成功!"<<endl;
                            break;
                        }
                        else {
                            cout << "分配失败!"<<endl;
                            break;
                        }
                    }//case2
                    case 3:
                    {
                        sort3(p_free,free);
                        bool result = worst_allocation(&p_free,&p_busy,now,free,busy,limit);
                        if(result) {
                            cout << "分配成功!"<<endl;
                            break;
                        }
                        else {
                            cout << "分配失败!"<<endl;
                            break;
                        }
                    }//case3
                    default:
                    {
                       cout<<"输入错误!"<<endl;
                       break;
                    }//default
                }//switch
             break;
            }//case1
            case 2:
            {
                int hid;
                cout<<"请输入要回收的作业id:"<<endl;
                cin>>hid;
                bool result =  recycle(&p_free,&p_busy,hid,free,busy);
                if(result) {
                    cout << "回收成功!"<<endl;
                    break;
                }
                else {
                    cout << "回收失败!"<<endl;
                    break;
                }
            }//case2
            case 3:
            {
                sort(p_busy,busy);

                cout<<"已分配区表:"<<endl;
                cout<<"起始地址"<<'\t'<<"长度"<<'\t'<<"标志"<<endl;
                for(int i = 0;i<p_busy;i++)
                    busy[i].print();
                cout<<"空闲区表:"<<endl;
                cout<<"起始地址"<<'\t'<<"长度"<<'\t'<<"标志"<<endl;
                for(int i = 0;i<p_free;i++)
                    free[i].print();
                break;
            }
            case 0:
                exit(0);
            default: {
                cout << "输入错误" << endl;
                break;
            }
        }//switch
    }
}
void sort( int p, area* queue)
{
    for(int i  = 0 ; i < p ; i++)
        for(int j = i + 1 ; j<p  ; j++)
        {
            if(queue[i].get_first_ad()>queue[j].get_first_ad())
            {
                area t = queue[j];
                queue[j] = queue[i];
                queue[i] = t;
            }
        }
}


bool first_allocation(int *pf,int *pb,work B, area *free, area *busy,int limit)
{
    sort(*pf,free);
    sort(*pb,busy);
    for(int i = 0;i<*pf;i++)
    {
        if(free[i].get_size()>=B.size)
        {
            if(free[i].get_size()-B.size<=limit)  //全部给出空间
            {
                busy[*pb].set_size(free[i].get_size());
                busy[*pb].set_first_ad(free[i].get_first_ad());
                busy[(*pb)++].set_flag(B.id);
                for(int j = i;j<*pf;j++)
                {
                    free[j] = free[j+1];
                }
                (*pf)--;

            }
            else{
                busy[*pb].set_size(B.size);
                busy[*pb].set_first_ad(free[i].get_first_ad());
                int last_ad = busy[*pb].compute_last_ad();
                busy[(*pb)++].set_flag(B.id);
                free[i].set_first_ad(last_ad+1);
                free[i].set_size(free[i].get_size()-B.size);
            }
            return true;
        }
    }
    return false;
}
bool best_allocation(int *pf,int *pb,work B,area *free,area *busy,int limit)
{
    sort2(*pf,free);
    sort(*pb,busy);
    int index = 0;
    int sign = 65535;
    for(int i = 0;i<*pf;i++)
    {
        if(free[i].get_size()<sign&&free[i].get_size()>=B.size) {
            index = i;
            sign = free[i].get_size();
        }
    }
    if(sign == 65535)
    {
        return false;
    }
    else{
        if(free[index].get_size()-B.size<=limit)  //全部给出空间
        {
            busy[*pb].set_size(free[index].get_size());
            busy[*pb].set_first_ad(free[index].get_first_ad());
            busy[(*pb)++].set_flag(B.id);
            for(int j = index;j<*pf;j++)
            {
                free[j] = free[j+1];
            }
            (*pf)--;

        }
        else{
            busy[*pb].set_size(B.size);
            busy[*pb].set_first_ad(free[index].get_first_ad());
            int last_ad = busy[*pb].compute_last_ad();
            busy[(*pb)++].set_flag(B.id);
            free[index].set_first_ad(last_ad+1);
            free[index].set_size(free[index].get_size()-B.size);
        }
        return true;
    }
}

bool worst_allocation(int *pf,int *pb,work B,area *free,area *busy,int limit)
{
    sort3(*pf,free);
    sort(*pb,busy);
    int index = -1;
    int sign  = -1;
    for(int i = 0;i<*pf;i++)
    {
        if(free[i].get_size()>sign&&free[i].get_size()>=B.size) {
            index = i;
            sign = free[i].get_size();
        }
    }
    if(index == -1)
    {
        return false;
    }
    else{
        if(free[index].get_size()-B.size<=limit)  //全部给出空间
        {
            busy[*pb].set_size(free[index].get_size());
            busy[*pb].set_first_ad(free[index].get_first_ad());
            busy[(*pb)++].set_flag(B.id);
            for(int j = index;j<*pf;j++)
            {
                free[j] = free[j+1];
            }
            (*pf)--;

        }
        else{
            busy[*pb].set_size(B.size);
            busy[*pb].set_first_ad(free[index].get_first_ad());
            int last_ad = busy[*pb].compute_last_ad();
            busy[(*pb)++].set_flag(B.id);
            free[index].set_first_ad(last_ad+1);
            free[index].set_size(free[index].get_size()-B.size);
        }
        return true;
    }
}
bool recycle(int *pf,int *pb,int id,area *free,area *busy)
{
    sort(*pf,free);
    sort(*pb,busy);
    int index = -1 ;
    for(int i = 0; i < *pb ;i++)
    {
        if(busy[i].get_flag() == id)
        {
            index = i;
            break;
        }
    }
    if(index == -1)
        return false;
    area a;
    a.set_first_ad(busy[index].get_first_ad());
    a.set_size(busy[index].get_size());
    a.set_flag(0);
    for(int i = index;i<*pb;i++)
    {
      busy[i] = busy[i+1];
    }
    (*pb)--;
    for(int i = 0;i<*pf;i++)
    {
        if((free[i].compute_last_ad()+1 ) == a.get_first_ad() && free[i+1].get_first_ad() == (a.compute_last_ad()+1))
        {
            free[i].set_size(free[i].get_size()+free[i+1].get_size()+a.get_size());
            for(int j = i+1;j<*pf;j++)
            {
                free[j]= free[j+1];
            }
            (*pf)--;
            return true;
        }
        else if((free[i].compute_last_ad()+1 ) == a.get_first_ad()){
            free[i].set_size(free[i].get_size()+a.get_size());
            return true;
        }
        else if(free[i].get_first_ad() == (a.compute_last_ad()+1))
        {
            free[i].set_first_ad(a.get_first_ad());
            free[i].set_size(free[i].get_size()+a.get_size());
            return true;
        }

    }
    free[(*pf)++] = a;
    return true;

}
