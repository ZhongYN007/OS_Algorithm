#include <iostream>
#include<string>

using namespace std;
typedef struct UFD {
    string File_name;
    string content;
    bool Is_read = true;
    bool Is_write = true;
}UFD;
typedef struct MFD {
    string user_name;
    UFD* user;
    int index = 0;
}MFD;
typedef struct AFD {
    UFD memory[5];
    int flag = 0;
}FD;
void Init(MFD* MFD);
bool Create(MFD& MFD);
bool open(MFD& MFD, FD& AFD);
bool read(FD& AFD);
bool write(FD& AFD);
bool close(FD& AFD);
bool Delete(FD& AFD, MFD& MFD);
int check(string name, MFD* MFD);
void second_menu(int pos, MFD* MFD, FD& AFD, int *mutex);
void print(MFD*MFD,int pos,AFD *AFD);
int main() {
    MFD MFD[10];
    Init(MFD);
    FD AFD;
    string name;
    int choice2;
    int mutex = 0;
    while (true) {
        cout << "欢迎使用文件控制系统" << endl;
        cout << "1.选择用户" << endl;
        cout << "0.退出" << endl;
        cin >> choice2;
        switch (choice2)
        {
            case 1: {
                cout << "请输入用户名";
                cin >> name;
                int pos;
                pos = check(name, MFD);
                second_menu(pos, MFD, AFD, &mutex);
                break;
            }
            case 0:
                exit(-1);
            default:
                cout << "输入有误，请重新选择" << endl;
        }
    }
}
void second_menu(int pos, MFD* MFD, FD& AFD,int *mutex)
{
    int choice;
    if (pos != -1)
    {
        while (true) {
            cout << "1.创建文件" << endl;
            cout << "2.打开文件" << endl;
            cout << "3.读文件" << endl;
            cout << "4.写文件" << endl;
            cout << "5.关闭文件" << endl;
            cout << "6.删除文件" << endl;
            cout<<"7.输出所有文件名"<<endl;
            cout << "0.退出该用户" << endl;

            cin >> choice;
            switch (choice) {
                case 1: {
                    if (Create(MFD[pos]))
                        cout << "创建成功！" << endl;
                    else
                        cout << "创建失败!" << endl;
                    break;
                }
                case 2: {
                    (*mutex)++;
                    if(*mutex <= 5) {

                        if (open(MFD[pos], AFD)) {
                            cout << "打开成功！" << endl;

                        } else {
                            cout << "打开失败!" << endl;
                            (*mutex)--;
                        }

                    }
                    else{
                        cout<<"打开文件超过上限(5个)"<<endl;
                        (*mutex)--;
                    }
                    break;
                }
                case 3: {
                    if (read(AFD))
                        cout << "读取成功！" << endl;
                    else
                        cout << "读取失败!" << endl;
                    break;
                }
                case 4: {
                    if (write(AFD))
                        cout << "写入成功！" << endl;
                    else
                        cout << "写入失败!" << endl;
                    break;
                }
                case 5: {

                    if (close(AFD))
                        cout << "关闭成功！" << endl;
                    else
                        cout << "关闭失败!" << endl;
                    break;
                }
                case 6: {
                    if (Delete(AFD, MFD[pos]))
                        cout << "删除成功！" << endl;
                    else
                        cout << "删除失败!" << endl;
                    break;
                }
                case 7:{
                    cout<<"该用户下的文件"<<endl;
                    print(MFD,pos,&AFD);
                    break;
                }
                case 0: {
                    return;
                }
                default:
                    cout << "输入有误，请重新选择";
            }
        }
    }
    else {
        cout << "没有该用户，请重新选择";
    }
}
int check(string name, MFD* MFD)
{
    for (int i = 0; i < 10; i++)
    {
        if (MFD[i].user_name == name)
            return i;
    }
    return -1;
}
void Init(MFD* MFD)
{
    for (int i = 0; i < 10; i++)
    {
        MFD[i].user = new UFD[10];
    }
    MFD[0].user_name= "user1";
    MFD[1].user_name ="user2";
    MFD[2].user_name ="user3";
    MFD[3].user_name ="user4";
    MFD[4].user_name ="user5";
    MFD[5].user_name ="user6";
    MFD[6].user_name ="user7";
    MFD[7].user_name ="user8";
    MFD[8].user_name ="user9";
    MFD[9].user_name ="user10";

}
bool Create(MFD &MFD)
{
    if (MFD.index >= 10)
    {
        cout << "超出数量" << endl;
        return false;
    }
    else {
        cout << "请输入文件名" << endl;
        string t;
        cin>>t;
        MFD.user[MFD.index].File_name = t;
        MFD.index++;
        return true;
    }
}

bool open(MFD& MFD, FD& AFD)
{
    cout << "请输入你要打开的文件名" << endl;
    string name;
    cin >> name;

    for (int i = 0; i < MFD.index; i++) {

        if (MFD.user[i].File_name == name)
        {

            //他在AFD中
            for (int j = 0; j < AFD.flag; j++) {

                if (AFD.memory[j].File_name == name) {
                    cout << "该文件已经打开" << endl;
                    return false;
                }
            }
            //不在AFD中
            AFD.memory[AFD.flag] = MFD.user[i];
            AFD.flag++;
            return true;
        }

    }
    cout << "该文件不存在" << endl;
    return false;

}
bool read(FD& AFD)
{
    cout << "请输入你要读取的文件名" << endl;
    string name;
    cin >> name;
    for (int i = 0; i < AFD.flag; i++)
    {
        if (AFD.memory[i].File_name == name)
        {
            if (!AFD.memory[i].Is_read)
            {
                cout << "该文件不可读取" << endl;
                return false;
            }
            else {
                cout << AFD.memory[i].content << endl;
                return true;
            }
        }

    }
    cout << "该文件不存在。";
    return false;

}
bool write(FD& AFD)
{
    cout << "请输入你要写入的文件名" << endl;
    string name;
    cin >> name;
    for (int i = 0; i < AFD.flag; i++)
    {
        if (AFD.memory[i].File_name == name)
        {
            if (!AFD.memory[i].Is_write)
            {
                cout << "该文件不可写入" << endl;
                return false;
            }
            else {
                cout << "请输入:" << endl;
                cin >> AFD.memory[i].content;
                return true;
            }
        }

    }

    cout << "该文件不存在。";
    return false;

}
bool close(FD& AFD)
{

    cout << "请输入你要关闭的文件名" << endl;
    string name;
    cin >> name;
    for (int i = 0; i < AFD.flag; i++)
    {
        if (AFD.memory[i].File_name == name)
        {

            for (int j = i; j < AFD.flag - 1; j++)
            {
                AFD.memory[j].File_name = AFD.memory[j + 1].File_name;
                AFD.memory[j].content = AFD.memory[j + 1].content;
                AFD.memory[j].Is_read = AFD.memory[j + 1].Is_read;
                AFD.memory[j].Is_write = AFD.memory[j + 1].Is_write;
            }

            AFD.flag--;
            cout << "关闭成功" << endl;
            return true;
        }

    }

    cout << "该文件不在AFD中。";
    return false;
}
bool Delete(FD& AFD, MFD& MFD)
{
    cout << "请输入你要删除的文件名" << endl;
    string name;
    cin >> name;
    for (int i = 0; i < AFD.flag; i++)
    {
        if (AFD.memory[i].File_name == name)
        {
            cout << "该文件已打开，不能删除。" << endl;
            return false;
        }
    }
    for (int i = 0; i < MFD.index; i++)
    {
        if (MFD.user[i].File_name == name)
        {
            for (int j = i; j < AFD.flag - 1; j++) {
                MFD.user[j].File_name = MFD.user[j + 1].File_name;
                MFD.user[j].content = MFD.user[j + 1].content;
                MFD.user[j].Is_read = MFD.user[j + 1].Is_read;
                MFD.user[j].Is_write = MFD.user[j + 1].Is_write;

            }
            MFD.index--;
            return true;
        }
    }
    return false;

}
void change_read(UFD& UFD)
{
    UFD.Is_read = false;
}

void change_write(UFD& UFD)
{
    UFD.Is_write = false;
}
void print(MFD*MFD,int pos,AFD *AFD)
{
    cout<<"UFD:"<<endl;
    for(int i  = 0;i<MFD->index;i++)
    {
        cout<<MFD[pos].user[i].File_name<<"\t";
    }
    cout<<endl;
    cout<<"AFD:"<<endl;
    for(int i  = 0;i<AFD->flag;i++)
    {
        cout<<AFD->memory[i].File_name<<"\t";

    }
    cout<<endl;
}