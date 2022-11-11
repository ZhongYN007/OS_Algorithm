#include <iostream>
using namespace std;
#define MAX_ADDRESS 128;
class  area{
 private:
     int size;
     int first_ad;
     int flag;  // 0为为分配， 其他数字分别代表区域id
 public:
     area(int size=0 , int first_ad = 0,int flag = 0) {
         this->size = size;
         this->first_ad = first_ad;
         this->flag = flag;
     }
     void print()
     {
         cout<<this->size<<this->first_ad<<this->flag;
     }
     int compute_end_ad(){
         return this->size+this->first_ad - 1;
     }
 };
struct work{
    int size;
    int id;
};
void allocation(work B, area* free , area* busy);  //1.
void sort(area* queue);  //首地址排序
void recycle(work B, area* free , area* busy);
int main() {

    area* free = new area[10];
    area* busy  = new area[10];

    area work1(8,0,1);
    area work2(32,30,2);
    area work3(4,80,3);
    area work4(2,10,4);

    busy[0] = work1;
    busy[1] = work2;
    busy[2] = work3;
    busy[3] = work4;



}
