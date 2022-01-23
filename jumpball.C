#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>
#define esc 27

int main() {
    int gd = DETECT, gm;
    int x[10], y[10], i, j, k=75;
    int flag[5]={0,0,0,0,0};
    int key=1;
    int key1=0;
    int score=0;
    char msg[128];
    int flag3=0,flag1=0,flag2=0;
    /* get mid positions in x and y-axis */
    int x1 = 100;
    int y1 = 215;       /*if y1+-10 does not lie between y[7] and 280,
	        then check for       wrong...rethink*/
    x[0] = 120;
    x[1]=x[0]+10;
    y[0] = 0;
    y[1]=150;

    for(i=2; i<7;i=i+2){
        x[i] = x[i-2] + 160;
        x[i+1] = x[i] + 10;
        y[i] = 0;
        y[i+1] = y[i-1] - 30;
    }

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    /* get mid positions in x and y-axis */
    settextstyle(9,HORIZ_DIR,5);
    outtextxy(80,100,"BALL BOUNCE");
    settextstyle(3,HORIZ_DIR,2);
    outtextxy(80,200,"ENTER 1 TO START...");
    outtextxy(80,240,"ENTER ANY OTHER KEY TO EXIT...");
    outtextxy(80,280,"'s' IS THE CONTROL KEY...");
    key=getch();
    if(key==49){
        while (kbhit()||key!=27) {
            setcolor(RED);
            setfillstyle(SOLID_FILL, RED);
            circle(x1, y1, 10);
            floodfill(x1, y1, RED);

            for(i=0;i<7;i=i+2){
                if(x[i] < 10)
                    flag[i] = !flag[i];
                /* draws the gray board */
                setcolor(RED);
                if(i==2)
                    setfillstyle(SOLID_FILL, 5);
                else if(i==4)
                    setfillstyle(SOLID_FILL, BLUE);
                else if(i==6)
                    setfillstyle(SOLID_FILL, 14);

                setfillstyle(SOLID_FILL, RED);
                if(i==0)
                    setfillstyle(SOLID_FILL, 5);
                else if(i==4)
                    setfillstyle(SOLID_FILL, BLUE);
                else if(i==6)
                    setfillstyle(SOLID_FILL, GREEN);
                if(i==2)
                    setfillstyle(SOLID_FILL, GREEN);
                else if(i==4)
                    setfillstyle(SOLID_FILL, BLUE);
                else if(i==6)
                    setfillstyle(SOLID_FILL, 14);
                if(flag[i]){
                    x[i]=getmaxx()-41;
                    x[i+1]=getmaxx()-31;
                    flag[i]=!flag[i];
                }
                else {
                    x[i]= x[i] - 5;
                    x[i+1]=x[i+1]-5;
                }
                rectangle(x[i], y[i], x[i+1], y[i+1]);
                rectangle(x[i], 280-15*i, x[i+1], getmaxy()-1);
                floodfill(x[i]+1, y[i]+1, RED);
                floodfill(x[i]+1, 281-15*i, RED);
                if(k>0){
                    outtextxy(k, getmaxy()/2, "START");
                    k--;
                }
                if(x[i+1]<90){
                    score=score+1;
                }

                if(x[i]<=(x1+10)&&(x1-10)<=x[i+1]&&((y1-10)<=y[i+1]||(y1+10)>=(280-15*i))){
                    while(kbhit()!=0)
                        key=getch();
                    cleardevice();
                    outtextxy(180,160,"GAME OVER");
                    sprintf(msg, "YOUR SCORE = %d", score);
                    outtextxy(180,200,msg);
                    delay(4000);
                    key=27;
                    key1=1;
                }
            }
            /* delay for 50 milli seconds */
            if(score<75)
                delay(45);
            else if(score<150)
                delay(22);
            else if(score<225)
                delay(8);
            else
                delay(0);
            /*flag3: if ball reaches bottom...
            flag2: if ball reaches top...
            flag1: if 's' is pressed*/
            if(kbhit()){
                if(getch()=='s')
                    flag1=1;
            }
            else
                flag1=0;
            if(y1 >= getmaxy()-10)
                flag3 =1;
            else
                flag3=0;
            if(y1<=10)
                flag2 = 1;
            else
                flag2=0;
            setcolor(RED);
            setfillstyle(SOLID_FILL, RED);
            circle(x1, y1, 10);
            floodfill(x1, y1, RED);

            if(flag1 && !flag2)
                y1 = y1 - 5;
            else if(!flag1 && flag3)
                y1=y1;
            else
                y1+=5;
            /* clears screen */
            cleardevice();
        }
    }
    else
        key1=1;
    if(!key1){
        sprintf(msg, "YOUR SCORE = %d", score);
        outtextxy(getmaxx()/2, getmaxy()/2,msg);
    }
    else{
        cleardevice();
    }
    getch();
    closegraph();
    return 0;
}

