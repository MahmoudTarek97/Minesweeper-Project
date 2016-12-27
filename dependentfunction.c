#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <pthread.h>
#include"global.h"
#include <winerror.h>
/*--------------------------------welcomeScreen function----------------------*/
void welcomeScreen()
{
    int i;
    char welcome[10]={'W','E','L','C','O','M','E',' ','T','O'};
    printf("\n");
    printf("                              "); Sleep(200);
    for (i=0;i<10;i++)
    {
        printf("%c",welcome[i]);
        Sleep(200);
    }
    printf("\n\n");
    printf("   ******************************************************************\n"
           "   *                                                                *\n"
           "   *                   ::      :: : ::  :  :::::                    *\n"
           "   *                   : :    : : : : : :  :                        *\n"
           "   *                   :  :  :  : : :  ::  :::::                    *\n"
           "   *                   :    :   : : :   :  :                        *\n"
           "   *                   :        : : :   :  :::::                    *\n"
           "   *                                                                *\n"
           "   *    :::::: :         :  ::::: :::::  ::::::  :::::   ::::::     *\n"
           "   *    :      :    :    :  :     :      :    :  :       ::    :    *\n"
           "   *    ::::::  :  : :  :   ::::  :::::  ::::::  :::::   ::::::     *\n"
           "   *         :   ::   ::    :     :      :       :       :: ::      *\n"
           "   *    ::::::    :   :     ::::: :::::  :       :::::   ::   ::    *\n"
           "   *                                                                *\n"
           "   ******************************************************************\n");
    printf("\n                       PRESS <ENTER> TO CONTINUE..");
    char c;
    c=getchar();
    while (c != '\n')
    {
        c=getchar();
    }
    clear();
    firstWelcome=1;
}
/*-------------------------------getCurrentPosition---------------------------*/
void getCurrentPosition(int *cX,int *cY)
{
    HANDLE hStdOut;
    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hStdOut, &csbiInfo);
    *cX = csbiInfo.dwCursorPosition.X;
    *cY = csbiInfo.dwCursorPosition.Y;
}
/*--------------------------------------gotoPosition--------------------------*/
void gotoPosition(int goX,int goY){
    HANDLE hStdOut;
    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD homeCoords = {goX,goY};
    SetConsoleCursorPosition( hStdOut,homeCoords );
}
/*--------------------------sortUsers-----------------------------------------*/
void sortUsers()
{
    int max =user[1].totalScore;
    int i,j,maxIndex;
    for(i=1;i<=userCounter;i++)
    {
        for (j=i;j<=userCounter;j++)
        {
            if (user[j].totalScore >= user[i].totalScore)
            {
                max=user[j].totalScore;
                maxIndex=j;
            }
            user[0]=user[maxIndex];
            user[maxIndex]=user[i];
            user[i]=user[0];
        }
    }
}
/*--------------------------------clear function------------------------------*/
void clear()
{
    system("cls");
}
/*----------------------------------color function---------------------------*/

void color(int k){
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
    //k=10 --> GREEN
    //k=11 --> LACTIC
    //k=12 --> RED
    //k=13 --> VIOLET
    //k=14 --> YELLOW
    //k=15 --> WHITE  default
