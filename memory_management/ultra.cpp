//
// Created by 钟雨农 on 2022/11/18.
//
#include<iostream>
using namespace std;
const double PI = 3.1415926;
class Point
{
public:
    int x, y;
    Point()
    {}
    Point(int x, int y)
    {
        this->x = x, this->y = y;
    }
};
class Shape
{
public:
    virtual double area() = 0;
};
class Circle :public Shape
{
private:
    Point center;
    double radious;
public:
    Circle(int x, int y, double radious)
    {
        center.x = x;
        center.y = y;
        this->radious = radious;
    }
    double area()
    {
        return(PI * radious * radious);
    }

};
class Rect :public Shape
{
private:
    Point p1, p2;
public:
    Rect(int x1, int y1, int x2, int y2)
    {
        p1.x = x1;
        p1.y = y1;
        p2.x = x2;
        p2.y = y2;
    }
    double area()
    {
        return(0.5 * abs(p2.x - p1.x) * abs(p2.y - p1.y));
    }
};
class Tri:public Shape
{
private:
    Point p1, p2, p3;
public:
    Tri(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        p1.x = x1;
        p1.y = y1;
        p2.x = x2;
        p2.y = y2;
        p3.x = x3;
        p3.y = y3;
    }
    double area()
    {
        return((1 / 2) * (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.x * p3.y - p2.x * p1.y - p3.x * p2.y));
    }
};
class Comparer
{
public:
    virtual int compare(Shape*ps1,Shape*ps2)=0;
};
class Sorter
{
public:
    virtual void sort(Shape*ps[],int count, Comparer*c)=0;
};
class XComparer:public Comparer
{
    virtual int compare(Point*ps1,Point*ps2)
    {
        return ps1->x-ps2->x;
    }

};
class YComperer:public Comparer
{
    virtual int compare(Point*ps1,Point*ps2)
    {
        return ps1->y-ps2->y;
    }
};
class Areacomparer:public Comparer
{

    virtual int compare(Shape*ps1,Shape*ps2)
    {
        return (ps1->area()-ps2->area());
    }
};
class BubbleSorter:public Sorter
{

    virtual void sort(Shape*ps[],int count, Comparer*c)
    {
        int i,j;
        for(i=0;i<count;i++)
        {
            for(j=0;j<count-i-1;j++)
            {
                if(c->compare(ps[j],ps[j+1])>0)
                {
                    Shape*t=ps[j];
                    ps[j]=ps[j+1];
                    ps[j+1]=t;
                }//if
            }//for1
        }//for2
    }
};
class SelectSorter:public Sorter
{

    virtual void sort(Shape*ps[],int count,Comparer*c)
    {
        int i,j,k;
        for(i=0;i<count ;i++)
        {
            k=i;
            for(j=i+1;j<count;j++)
            {
                if(c->compare(ps[k],ps[j])>0)
                    k=j;
            }//for
            if(k!=i)
            {
                Shape*t=ps[k];
                ps[k]=ps[i];
                ps[i]=t;

            }//if

        }//for
    }//sort
};
typedef   Shape* PShape;
int main()
{
    srand((int)time(0));

    int count = 10, i, choice;
    PShape* ps = new PShape[count];

    for (i = 0; i < count; i++) {
        choice = rand() % 3;
        switch (choice) {
            case 0: ps[i] = new Circle(rand() % 100, rand() % 100, rand() % 100); break;
            case 1: ps[i] = new Rect(rand() % 100, rand() % 100, rand() % 100, rand() % 100); break;
            case 2: ps[i] = new Tri(rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100, rand() % 100); break;
        }
    }

    for (i = 0; i < count; i++) {
        printf("Shape %d Area = %lf\n", i, ps[i]->area());
    }

    cout << "----------------------" << endl;

    Sorter* s = new SelectSorter();
    Comparer*c = new Areacomparer();

    s->sort(ps, count,c );
    for (int i = 0; i < count; i++)
        cout << "Shape " << i << " Area = " << ps[i]->area() << endl;
    for (i = 0; i < count; i++)
    {
        delete ps[i];
    }
    delete[] ps;
}