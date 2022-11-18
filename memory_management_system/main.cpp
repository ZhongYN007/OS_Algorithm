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
        cout<<this->size<<this->first_ad<<this->flag;
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
};

struct work{
    int size;
    int id;
};
void first_allocation(int pf,int pb,work B, area *free, area *busy);
void best_allocation(int pf,int pb,work B,area *free,area *busy);
void worst_allocation(int pf,int pb,work B,area *free,area *busy);
void recycle(int pf,int pb,work B,area *free,area *busy);
void sort(int p, area *queue);




int main()
{
    area *free  = new area[MAX_ADDRESS];
    area *busy  = new area[MAX_ADDRESS];
    int p_free = 0;
    int p_busy = 0;
    area work1(8,0,1);
    area work2(32,30,2);
    area work3(4,80,3);
    area work4(2,10,4);
    busy[0] = work1;
    busy[1] = work2;
    busy[2] = work3;
    busy[3] = work4;

}
void sort( int p, area* queue)
{
    for(int i  = 0 ; i < p ; i++)
        for(int j = i + 1 ; j<p - 1  ; j++)
        {
            if(queue[i].get_first_ad()>queue[j].get_first_ad())
            {
                area t = queue[j];
                queue[j] = queue[i];
                queue[i] = t;
            }
        }
}
void add()
{}