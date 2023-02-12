#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <direct.h>
 
#define W 80     
#define H 37     
#define SNAKE_ALL_LENGTH 200    
using namespace std;
 
void CALLBACK TimerProc(
        HWND hwnd,       
        UINT message,     
        UINT idTimer,     
        DWORD dwTime);
void start();
 
struct MYPOINT
{
    int x;
    int y;
} s[SNAKE_ALL_LENGTH] , head, end, food;
 
int max_count=0; 
int old_max_count=0;   
int count=0;  
int len=20;  
int direct=0;
int speed=200;   
bool isfood=false; 
int timerID;
bool stop=false;    
char* ini_path=new char[50];  
  
void setxy(int x, int y)  
{
   COORD coord = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
void hide_cursor() 
{
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = sizeof(cci);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cci);
}
 
void set_food()       
{
    if(isfood==true)
    {
        return;
    }
    int x,y;
    bool flag=false;
    while(1)
    {
        flag=false;
        x=rand()%(W-14)+6;
        y=rand()%(H-12)+6;
        for(int i=0;i<len;i++)      
        {
            if(s[i].x==x && s[i].y==y)
            {
                flag=true;
                break;
            }
        }
        if(flag==true)
        {
            continue;
        }
        else
        {
            food.x=x;
            food.y=y;
            break;
        }
    }
    setxy(food.x,food.y);
    cout<<"*";
    isfood=true;
}
 
void check_board()    
{
    if(s[0].x>=W-3 || s[0].x<=2 || s[0].y>=H-1 || s[0].y<=2)
    {
        setxy(W/2-5,0);
        cout<<"game over"<<endl;
        stop=true;
        if(old_max_count<max_count)
        {
            char t[5]={'\0'};
            sprintf(t,"%d",max_count);
            WritePrivateProfileString("MAX_COUNT","max_count",t,ini_path);
        }
    }
    for(int i=1;i<len;i++)
    {
        if(s[i].x==s[0].x && s[i].y==s[0].y)
        {
            setxy(W/2-5,0);
            cout<<"game over"<<endl;
            stop=true;
            if(old_max_count<max_count)
            {
                char t[5]={'\0'};
                sprintf(t,"%d",max_count);
                WritePrivateProfileString("MAX_COUNT","max_count",t,ini_path);
            }
            break;
        }
    }
    if(stop==true)
    {
        KillTimer(NULL,timerID);
        int c;
        while(1)
        {
            fflush(stdin);
            c=_getch();
            if(c=='n' || c=='N')
            {
                start();
            }
            else if(c=='q' || c=='Q')
            {
                exit(0);
            }
            else continue;
        }
    }
}
 
void printf_body(bool is_first=false)   
{
    if(is_first==true)     
	    {
 
        for(int i=0;i<len;i++)
        {
            setxy(s[i].x,s[i].y);
            cout<<"O";
        }
    }
    else                  
    {
        setxy(end.x,end.y);
        cout<<" ";
        setxy(s[0].x,s[0].y);
        cout<<"O";
    }
    if(food.x==s[0].x && food.y==s[0].y) 
    {
        count++;
        isfood=false;                     //重置食物 
        set_food();
        len++;
        KillTimer(NULL,timerID);
        if(speed>100) speed-=10;
        else if(speed>50) speed-=5;
        else if(speed>30) speed-=2;
        else if(speed>16) speed-=1;
        else ;
        setxy(0,0);
        if(max_count<count)  max_count=count;
        cout<<"  speed : "<<speed<<" ms     score : "<<count<<"                                   best score:"<<max_count<<"  ";
        timerID=SetTimer(NULL,001,speed,TimerProc);
    }
}
 
void change_body_pos(int x, int y)   //改变蛇身的坐标数据 
{
    end.x=s[len-1].x;
    end.y=s[len-1].y;
    for(int i=len-1;i>0;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    s[0].x=x;
    s[0].y=y;
}
void CALLBACK TimerProc(
        HWND hwnd,       
        UINT message,     
        UINT idTimer,     
        DWORD dwTime)
{
    switch(direct)
    {
        case 0:
            head.x++;
            change_body_pos(head.x,head.y);
            printf_body();
            check_board();
            break;
        case 1:
            head.y++;
            change_body_pos(head.x,head.y);
            printf_body();
            check_board();
            break;
        case 2:
            head.x--;
            change_body_pos(head.x,head.y);
            printf_body();
            check_board();
            break;
        case 3:
            head.y--;
            change_body_pos(head.x,head.y);
            printf_body();
            check_board();
            break;
    }
}
 
void start()
{
    KillTimer(NULL,timerID);
    count=0;  //得分 
    len=20;   //当前蛇身长度 
    direct=0; //方向: 0-向右, 1-向下, 2-向左, 3-向上
    speed=200;  //速度:毫秒 
    isfood=false; //食物是否存在
    stop=false;   //停止 
    system("cls");
    setxy(1,4);
    cout<<"┌─────────────────────────────────────┐"<<endl;
    for(int i=0;i<33;i++)
    {
        cout<<" │                                                                          │"<<endl;
    }
    cout<<" └─────────────────────────────────────┘";
    head.x=len-1+5;
    head.y=H/2;
    for(int i=0;i<len;i++)
    {
        s[i].x=head.x-i;
        s[i].y=head.y;
    }
    setxy(0,0);
    cout<<"  speed : "<<speed<<" ms     score : "<<count<<"                                   best score:"<<max_count<<"  ";
    printf_body(true);
    set_food();
    timerID=SetTimer(NULL,001,speed,TimerProc);
    int c;
    MSG msg;
    while(GetMessage(&msg,NULL,0,0))
    {
        if(stop==true)  break;
        if(_kbhit())   //如果按下的是方向键或功能键, _getch()要调用两次,第一次返回0XE0或0 
        {
            fflush(stdin);
            c=_getch();   //上: 72 下:80  左:75  右:77 
            if(c==0XE0 || c==0)
            {
                c=_getch();
                if(c==72 && direct!=1 && direct!=3)
                {
                    direct=3;
                }
                else if(c==80 && direct!=1 && direct!=3)
                {
                    direct=1;
                }
                else if(c==75 && direct!=0 && direct!=2)
                {
                    direct=2;
                }
                else if(c==77 && direct!=0 && direct!=2)
                {
                    direct=0;
                }
            }
            else if(c==' ')
            {
                setxy(W/2-10,0);
                system("pause");
                setxy(W/2-10,0);
                cout<<"                    ";
            }
        }
        if(msg.message==WM_TIMER)
        {
            DispatchMessage(&msg);
        }
    }
}
 
int main()
{
    srand((unsigned)time(0));
    getcwd(ini_path,50);//取得当前程序绝对路径
    ini_path=strcat(ini_path,"snake.dat");
     
    max_count=GetPrivateProfileInt("MAX_COUNT","max_count",0,ini_path);
    old_max_count=max_count;
    char cmd[50];
    sprintf(cmd,"mode con cols=%d lines=%d\0",W,H);
    system(cmd);//改变CMD窗口大小
    hide_cursor();
    start();
    return 0;
}
