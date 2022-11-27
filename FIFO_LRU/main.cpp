#include<iostream>
using namespace std;

void FIFO(int length, int size, int* page, int** margin, bool* lose);//先进先出
void LRU(int length, int size, int* page, int** margin, bool* lose);//最近最少使用
int find(int a, int* str,int size);  //在内存中查找对应页
void print(int** margin, int *page, bool* lose, int size, int length);//输出

int main()
{
    int length;
    int size;
    cout << "请输入页面长度：" << endl;
    cin >> length;

    int* page =new int[length];
    cout << "请按顺序输入页面：" << endl;
    for (int i = 0; i < length; i++)
    {
        cin >> page[i];
    }

    cout << "请输入页框长度：" <<endl;
    cin >> size;

    int** margin = new int* [size];//记录整体情况
    for (int i = 0; i < size; i++)//为记录表分配空间
    {
        margin[i] = new int[length];
    }

    for (int i = 0; i < size; i++)//初始化记录表
        for (int j = 0; j < length; j++)
            margin[i][j] = 0;

    bool* lose = new bool[length];//记录是否发生缺页
    for (int i = 0; i < length; i++)
    {
        lose[i] = false;
    }

    cout << "FIFO算法：" << endl;
    FIFO(length, size, page, margin, lose);
    print(margin, page, lose, size, length);

    for (int i = 0; i < size; i++)//将各表重新初始化
        for (int j = 0; j < length; j++)
            margin[i][j] = 0;
    for (int i = 0; i < length; i++)
    {
        lose[i] = false;
    }

    cout << "LRU算法：" << endl;
    LRU(length, size, page, margin, lose);
    print(margin, page, lose, size, length);
}

int find(int a, int* str,int size)//在内存中查找对应页
{
    for (int i = 0; i < size; i++)
    {
        if (a == str[i])//找到了
            return(i);
    }
    return(-1);
}

void FIFO(int length, int size, int* page, int** margin, bool* lose)
{
    int *str=new int[size];//str记录当前内存存放情况
    for (int i = 0; i < size; i++)//初始化str
    {
        str[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        if (find(page[i],str,size)!=-1)//查找成功
        {
            lose[i] = true;
            for (int j = 0; j < size; j++)//更新记录表
            {
                margin[j][i] = str[j];
            }
        }
        else//缺页中断
        {
            for (int j = size-1; j > 0; j--)//更新str
            {
                str[j] = str[j-1];
            }
            str[0] = page[i];

            for (int j = 0; j < size; j++)//更新记录表
            {
                margin[j][i] = str[j];
            }
            lose[i] = false;
        }
    }
}

void LRU(int length, int size, int* page, int** margin, bool* lose)
{
    int* str = new int[size];
    for (int i = 0; i < size; i++)//初始化str
    {
        str[i] = 0;
    }
    for (int i = 0; i < length; i++)
    {
        if (find(page[i], str, size) != -1)//查找成功
        {
            int index = find(page[i], str, size);
            int t = str[index];
            for (int j = index; j > 0; j--)//更新str
            {
                str[j] = str[j-1];
            }
            str[0] = t;
            lose[i] = true;
            for (int j = 0; j < size; j++)//更新记录表
            {
                margin[j][i] = str[j];
            }
        }
        else//缺页中断
        {
            for (int j = size - 1; j > 0; j--)//更新str
            {
                str[j] = str[j - 1];
            }
            str[0] = page[i];

            for (int j = 0; j < size; j++)//更新记录表
            {
                margin[j][i] = str[j];
            }
            lose[i] = false;
        }
    }
}

void print(int** margin, int *page ,bool* lose, int size, int length)
{
    int num = 0;
    for (int i = 0; i < length; i++)
        cout << page[i] << '\t';
    cout << endl;
    cout << endl;
    cout << endl;
    for (int i = 0; i < size; i++)//输出记录表
    {
        for (int j = 0; j < length; j++)
        {

            if (margin[i][j] == 0)
                cout << " " << '\t';
            else
                cout << margin[i][j] << '\t';
        }
        cout << endl;
    }
    for (int i = 0; i < length; i++)//输出缺页情况
    {
        if (lose[i] == false)
        {
            cout << "X" << '\t';
            num++;
        }
        else
            cout << "V" << '\t';
    }
    cout << endl;
    cout << "共发生缺页中断次数为：" << num << endl;
}