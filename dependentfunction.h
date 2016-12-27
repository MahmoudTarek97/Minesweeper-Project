#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <pthread.h>
#include <winerror.h>
/*--------------------------------mainMenu function-----------------------------*/
void mainMenu(){
        clear();
        color(14);
        printf("\n\n   MAIN MENU\n   ---------\n\n");
        color(15);
        printf("     1\) NEW GAME \n\n     2\) LOAD GAME \n\n     3\) LEADERBOARD \n\n\
     4\) INSTRUCTIONS \n\n     5\) EXIT GAME\n\n\n");
    }
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
    int i,qwe,maxIndex;
    for(i=1;i<=userCounter;i++)
    {
        for (qwe=i;qwe<=userCounter;qwe++)
        {
            if (user[qwe].totalScore >= user[i].totalScore)
            {
                max=user[qwe].totalScore;
                maxIndex=qwe;
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

/*-------------------------------showInstructions Function--------------------*/
void showInstructoins()
{
    color(14);
    printf("\n\n   GAME RULES"
            "\n   ----------");
    color(15);
    printf( "\n\n   You must customize your own minefield.\n"
            "   At the beginning, open any cell in the minefield randomly to expose free space.\n"
            "   The numbers displayed show how many mines are adjacent to that cell.\n"
            "   Use your math skills and powers of deduction to identify where the mines must be.\n"
            "   Place a flag where you know a mine to be and open up cells where you think there isn't one.\n"
            "   In case that you are not sure there is a mine in certain cell or not ,\n"
            "   you can mark this cell by placing a question mark,\n"
            "   it might help you later. At anytime you can unmark that cell.\n\n"
            "   To win; open every cell that does not contain a mine. Be quick as you can and use\n"
            "   the minimum number of movements to get high score .\n"
            "   (every action you entered is a movement)\n"
            "   Be careful, don't hit any mine so as not to lose.\n\n"
            "   Many surprises await you. Enjoy!");
    color(14);
    printf("\n\n\n   HOW TO PLAY ?\n   -----------");
    color(15);
    printf("\n    Enter a symbol of your action then enter cell coordinates\n");
    printf("\n    Available Actions :");
    printf("\n     - Grid Actions\t\t\t- Game Actions");
    printf("\n        * <o> : Open Cell\t\t  * <s> : Save Game");
    printf("\n        * <f> : Flag cell\t\t  * <b> : Back to MAIN MENU");
    printf("\n        * <?> : Mark cell");
    printf("\n        * <u> : Unmark cell\n\n");
}
