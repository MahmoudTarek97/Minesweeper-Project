#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <pthread.h>
#include"global.h"
#include"independentfunction.h"
#include"saveloadgetboardaddwiner.h"
#include"initialplay.h"
#include"select.h"
#include"userfunctionthread.h"
#include"otherfunction.h"

/*--------------------------------main function-----------------------------*/
int main(){
        color(15);
        system("mode 150");
        //welcome
        if(firstWelcome==0)
        {
            char *NewDir = "Data";
            CreateDirectory(NewDir,NULL);
            color(11);
            welcomeScreen();
            color(15);
        }
        // some declarations :)
        char gridView[MAX_LEN][MAX_LEN];
        int gridNum[MAX_LEN][MAX_LEN];
        int gridVisited[MAX_LEN][MAX_LEN];
        int choice;

        // the main code
        j=0;
        GetLeaderBoard();
        mainMenu();
        choice = Selection();
        clear();

        if (choice ==1)     //New Game
            {
                color(14);
                printf("\n\n   NEW GAME\n   --------\n");
                color(15);
                printf("    Dimensions of your grid < Rows x Columns >\n");
                printf("        Min is 2 x 2 and Max is 30 x 30\n\n");

                //scan Rows
                while (1)
                {
                    color(10);
                    printf("\n    -> Enter number of Rows : ");
                    color(15);
                    char gridRows[500];
                    readChoice(gridRows,MAX_LEN);
                    fflush(stdin);
                    int Validity=numberCheck(gridRows,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                        {
                            Rows = numberValue(gridRows,MAX_LEN,Validity);
                            break;
                        }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
                printf("\n");
                //scan Columns
                while (1)
                {
                    color(10);
                    printf("\n    -> Enter number of Columns : ");
                    color(15);
                    char gridColumns[500];
                    readChoice(gridColumns,MAX_LEN);
                    fflush(stdin);
                    int Validity=numberCheck(gridColumns,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                        {
                            Columns = numberValue(gridColumns,MAX_LEN,Validity);
                            break;
                        }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }

                color(15);
                printf("\a");
                clear();
                time(&startTime);
                endTime=startTime;
                numberOfMines=1+((Rows*Columns)/10);
                initializeGrid(Rows,Columns,gridView,gridNum,gridVisited);
                printGrid(Rows,Columns,gridView);
                userAction(Rows,Columns,gridView,gridNum,gridVisited);
            }
        if (choice ==2)     //Load Game
            {
                loadGame(gridNum,gridView,gridVisited);
                if (Rows==0 /*||Columns ==0*/)
                {
                    printf("\n\n   you did not save any game yet!");
                    Sleep(1000);
                    main();
                    return 0;
                }
                printf("\n\n   Your last game will be loaded..\n");
                Sleep(2000);
                clear();
                time(&startTime);
                endTime=startTime;
                printGrid(Rows,Columns,gridView);
                debugGrid(Rows,Columns,gridNum);
                userAction(Rows,Columns,gridView,gridNum,gridVisited);
            }
        if (choice ==3)     //Leaderboard
            {
                printLeaderBoard();
            }
        if (choice ==4)     //Instructions
            {
                showInstructoins();
                while(1)
                {
                    color(10);
                    printf("    --> Enter <b> to back to MAIN MENU : ");
                    color(15);
                    char backChoice[500];
                    readChoice(backChoice,500);
                    fflush(stdin);
                    if (backChoice[0]=='b' && backChoice[1]=='\0')
                    {
                        break;
                    }
                }
                main();
            }
        if (choice ==5)     //Exit
            {
                    printf("\n\n   Are you sure you want to Exit?\n");
                    char exitChoice[500];
                    while(1)
                    {
                        color(10);
                        printf("    --> Enter <y or n> : ");
                        color(15);
                        readChoice(exitChoice,500);
                        fflush(stdin);
                        if ((exitChoice[0] =='y' || exitChoice[0] =='n') && exitChoice[1]=='\0')
                            break;
                    }
                    if (exitChoice[0]=='y')
                        printf("   GoodBye :)");
                    else
                        main();
            }
        return 0;
}
