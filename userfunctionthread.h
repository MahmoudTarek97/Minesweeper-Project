



/*-----------------------------------myThreadFunction-----------------------------*/
void *myThreadFun(void *vargp)
{
    int timerr=orgDiff;
    Sleep(1);
    int y;
    time_t start_t;
    time(&start_t);
    time(&initial_t);
    while(1)
    {
        if(j==0)
        {
            time_t  end_t;
            time(&end_t);
            y=end_t-start_t;
            int deltay =end_t-initial_t;
            if(y==1)
            {
                timerr=timerr+1;
                orgDiff=timerr;
                if(deltay%20==0&&ssd==0)
                {
                    int diffInMin = timerr/60;
                    int diffInSec = timerr%60;
                    ssd=0;
                    color(12);
                    int xp,yp;
                    getCurrentPosition(&xp,&yp);
                    /////
                    gotoPosition(0,0);
                    printf("   Warning: %d minute(s) passed without any input !",deltay/20);
                    gotoPosition(19,22);
                    printf("%0.2d:%0.2d\n",diffInMin,diffInSec); color(15);
                    gotoPosition(xp,yp);
                    //////
                }
            time(&start_t);
            }
        }
        else
            pthread_exit(NULL);
    }

    return NULL;
}
/*-------------------------------UserAction function---------------------------*/
void userAction(int Rows, int Columns,char gridView[][MAX_LEN],int
gridNum[][MAX_LEN],int gridVisited[][MAX_LEN]){

    pthread_t tid;
    pthread_create(&tid,NULL, myThreadFun,NULL);
    while(1)
        {
        if (numberOfMovements==0) printf("\n");
        if (numberOfMovements>0)
        {
            color(14);
            printf("\n   -> Last Action %c <%d,%d>",action[0],x+1,y+1);
            color(15);
        }
        if (lose ==1)
        {
            //lose
            j=1;
            char lose[]={"***GAME OVER***"};
            int c;
            int xp,yp;
            printf("\n\t\t\t");
            getCurrentPosition(&xp,&yp);
            for(c=0;c<15;c++)
            {
                printf("%c",lose[c]);
                Sleep(250);
            }
            gotoPosition(xp,yp);    color(12);  printf("%s",lose);   Sleep(250);    color(15);
            return 0;
        }
        if (win==1)
        {
            //win
            j=1;
            printf("\n");
            char win[]={"***YOU WIN***"};
            int c;
            int xp,yp;
            printf("\n\t\t\t");
            getCurrentPosition(&xp,&yp);
            for(c=0;c<13;c++)
            {
                printf("%c",win[c]);
                Sleep(250);
            }
            gotoPosition(xp,yp);    color(11);  printf("%s",win);   Sleep(250);
            gotoPosition(xp,yp);    color(15);  printf("%s",win);   Sleep(250);
            gotoPosition(xp,yp);    color(11);  printf("%s",win);   Sleep(250);   color(15);
            addWinner();
            return 0;
        }
        while(1)
        {
            color(10);
            printf("\n    --> Action : ");
            color(15);
            time(&endTime);
            TimeDiff = endTime - startTime ;
            orgDiff=TimeDiff+savedTimeDiff;
            lazyUserInput(orgDiff,action);
            fflush(stdin);

            if ( (action[0]=='o' ||action[0]=='f' ||action[0]=='?' ||action[0]=='u' ||action[0]=='s' ||action[0]=='b') && action[1]=='\0')
                break;
            else
            {
                color(12);
                printf("\t\t\t\t\tInvalid action !");
                color(15);
            }
        }

        if (action[0] == 'o')
        {
            //open cell
            while(1)
            {
                color(10);
                printf("\n    --> Row : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charRows[500];
                lazyUserInput(orgDiff,charRows);
                fflush(stdin);
                if ((charRows[0]=='1' || charRows[0]=='2') && charRows[1]=='\0')
                {
                    x=charRows[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charRows,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                    {
                        x = numberValue(charRows,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }

            while(1)
            {
                color(10);
                printf("\n    --> Column : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charColumns[500];
                lazyUserInput(orgDiff,charColumns);
                fflush(stdin);
                if ((charColumns[0]=='1' || charColumns[0]=='2') && charColumns[1]=='\0')
                {
                    y=charColumns[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charColumns,MAX_LEN);
                   if (Validity == 1 || Validity==2)
                    {
                        y = numberValue(charColumns,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }
            x--;
            y--;
            clear();
            time(&endTime);
            TimeDiff = endTime - startTime ;
            if (x > Rows-1 || y > Columns-1 )
            {
                printf("   Error: Invalid Coordinates!");
                printGrid(Rows,Columns,gridView);
            }
            else
            {
                if (check==0) //first play
                {
                generateMines(Rows,Columns,gridView,gridNum,x,y);
                debugGrid(Rows,Columns,gridNum);
                check=1;
                }

                if(gridView[x][y]=='X')
                {
                    openCell(x,y,Rows,Columns,gridView,gridNum,gridVisited);
                    numberOfMovements++;
                    printGrid(Rows,Columns,gridView);
                }
                else if(gridView[x][y]=='F')
                {
                    openCell(x,y,Rows,Columns,gridView,gridNum,gridVisited);
                    numberOfMovements++;
                    flaggedCells--;
                    printGrid(Rows,Columns,gridView);
                }
                else if(gridView[x][y]=='?')
                {
                    openCell(x,y,Rows,Columns,gridView,gridNum,gridVisited);
                    numberOfMovements++;
                    printGrid(Rows,Columns,gridView);
                    markedCells--;
                }
                else if (gridView[x][y]>='1' && gridView[x][y]<='8')
                {
                    numberOfMovements++;
                    if ( flagsArCell(x,y,Rows,Columns,gridView) == gridNum[x][y])
                    {

                        if(x-1>=0 && y-1>=0 && gridView[x-1][y-1]!='F')
                        openCell(x-1,y-1,Rows,Columns,gridView,gridNum,gridVisited);

                        if(x-1>=0&&gridView[x-1][y]!='F')
                        openCell(x-1,y,Rows,Columns,gridView,gridNum,gridVisited);

                        if(x-1>=0 && y+1<Columns && gridView[x-1][y+1]!='F')
                        openCell(x-1,y+1,Rows,Columns,gridView,gridNum,gridVisited);

                        if(y-1>=0 && gridView[x][y-1]!='F')
                        openCell(x,y-1,Rows,Columns,gridView,gridNum,gridVisited);

                        if(y+1<Columns && gridView[x][y+1]!='F')
                        openCell(x,y+1,Rows,Columns,gridView,gridNum,gridVisited);

                        if(x+1<Rows && y-1>=0 && gridView[x+1][y-1]!='F')
                        openCell(x+1,y-1,Rows,Columns,gridView,gridNum,gridVisited);

                        if(x+1<Rows && gridView[x+1][y]!='F')
                        openCell(x+1,y,Rows,Columns,gridView,gridNum,gridVisited);

                        if(x+1<Rows && y+1<Columns && gridView[x+1][y+1]!= 'F')
                        openCell(x+1,y+1,Rows,Columns,gridView,gridNum,gridVisited);

                        printGrid(Rows,Columns,gridView);

                    }

                    else
                    {
                        numberOfMovements++;
                        printGrid(Rows,Columns,gridView);
                    }

                }
                else //that mean : user try to open empty cell
                {
                        numberOfMovements++;
                        printGrid(Rows,Columns,gridView);
                }

            }
        }
        else if (action[0] == 'f')
        {
            // flag cell
            while(1)
            {
                color(10);
                printf("\n    --> Row : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charRows[500];
                lazyUserInput(orgDiff,charRows);
                fflush(stdin);
                if ((charRows[0]=='1' || charRows[0]=='2') && charRows[1]=='\0')
                {
                    x=charRows[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charRows,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                    {
                        x = numberValue(charRows,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }

            while(1)
            {
                color(10);
                printf("\n    --> Column : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charColumns[500];
                lazyUserInput(orgDiff,charColumns);
                fflush(stdin);
                 if ((charColumns[0]=='1' || charColumns[0]=='2') && charColumns[1]=='\0')
                {
                    y=charColumns[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charColumns,MAX_LEN);
                   if (Validity == 1 || Validity==2)
                    {
                        y = numberValue(charColumns,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }
            x--;
            y--;
            clear();
            time(&endTime);
            TimeDiff = endTime - startTime ;
            if (x > Rows-1 || y > Columns-1 )
            {
                printf("   Error: Invalid Coordinates! your Grid is only %d x %d",Rows,Columns);
                printGrid(Rows,Columns,gridView);
            }
            else
            {
                numberOfMovements++;
                if (flaggedCells>=numberOfMines)
                {
                    printf("   Error: Your Flags will exceed the Number of Mines!");
                }
                else if (gridView[x][y] =='X')
                {
                    gridView[x][y]='F';
                    flaggedCells++;
                }
                else if (gridView[x][y] =='?')
                {
                    gridView[x][y]='F';
                    flaggedCells++;
                    markedCells--;
                }

                printGrid(Rows,Columns,gridView);
            }
        }

        else if (action[0] == '?')
        {
            //? cell
            numberOfMovements++;
            while(1)
            {
                color(10);
                printf("\n    --> Row : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charRows[500];
                lazyUserInput(orgDiff,charRows);
                fflush(stdin);
                if ((charRows[0]=='1' || charRows[0]=='2') && charRows[1]=='\0')
                {
                    x=charRows[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charRows,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                    {
                        x = numberValue(charRows,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }

            while(1)
            {
                color(10);
                printf("\n    --> Column : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charColumns[500];
                lazyUserInput(orgDiff,charColumns);
                fflush(stdin);
               if ((charColumns[0]=='1' || charColumns[0]=='2') && charColumns[1]=='\0')
                {
                    y=charColumns[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charColumns,MAX_LEN);
                   if (Validity == 1 || Validity==2)
                    {
                        y = numberValue(charColumns,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }
            x--;
            y--;
            clear();
            time(&endTime);
            TimeDiff = endTime - startTime ;
            if (x > Rows-1 || y > Columns-1 )
            {
                printf("   Error: Invalid Coordinates! How Do you want to Mark Non-Existent Cell! TELL ME");
                printGrid(Rows,Columns,gridView);
            }
            else
            {
                if (gridView[x][y] =='X')
                {
                    gridView[x][y]='?';
                    markedCells++;
                }
                else if (gridView[x][y] =='F')
                {
                    gridView[x][y]='?';
                    markedCells++;
                    flaggedCells--;
                }
                printGrid(Rows,Columns,gridView);
            }
        }

        else if (action[0] == 'u')
        {
            //unmark cell
            numberOfMovements++;
            while(1)
            {
                color(10);
                printf("\n    --> Row : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charRows[500];
                lazyUserInput(orgDiff,charRows);
                fflush(stdin);
                if ((charRows[0]=='1' || charRows[0]=='2') && charRows[1]=='\0')
                {
                    x=charRows[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charRows,MAX_LEN);
                    if (Validity == 1 || Validity==2)
                    {
                        x = numberValue(charRows,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }

            while(1)
            {
                color(10);
                printf("\n    --> Column : ");
                color(15);
                time(&endTime);
                TimeDiff = endTime - startTime ;
                orgDiff=TimeDiff+savedTimeDiff;
                char charColumns[500];
                lazyUserInput(orgDiff,charColumns);
                fflush(stdin);
                if ((charColumns[0]=='1' || charColumns[0]=='2') && charColumns[1]=='\0')
                {
                    y=charColumns[0]-'0';
                    break;
                }
                else
                {
                    int Validity=numberCheck(charColumns,MAX_LEN);
                   if (Validity == 1 || Validity==2)
                    {
                        y = numberValue(charColumns,MAX_LEN,Validity);
                        break;
                    }
                    else
                    {
                        color(12);
                        printf("\t\t\t\t\tInvalid number !");
                        color(10);
                    }
                }
            }
            x--;
            y--;
            time(&endTime);
            TimeDiff = endTime - startTime ;
            clear();
            if (x > Rows-1 || y > Columns-1 )
            {
                printf("   Error: Invalid Coordinates! You are Malicious user");
                printGrid(Rows,Columns,gridView);
            }
            else
            {
                if (gridView[x][y] =='F')
                {
                    gridView[x][y]='X';
                    flaggedCells--;
                }
                else if (gridView[x][y] =='?')
                {
                    gridView[x][y]='X';
                    markedCells--;
                }
                printGrid(Rows,Columns,gridView);
            }
        }
        else if (action[0] == 's')
        {
            j=1;
            time(&endTime);
            TimeDiff = endTime - startTime ;
            printf("   \t\t\tSaving..");
            Sleep(1000);
            saveGame(gridNum,gridView,gridVisited);
            return 0;
        }

        else if (action[0] == 'b')
        {
            j=1,win=0,lose-0;
            startTime=0,endTime=0,TimeDiff=0;
            numberOfMovements = 0;
            score = 0;
            flaggedCells = 0;
            markedCells = 0;
            check =0;
            savedTimeDiff=0;
            main();
            return 0;
        }
        lastAction = action[0];
     ////////////////////
            int i,j;
            printf("\n");
            i=0;j=0;
            
            /////////////////////*/
        }
        pthread_join(tid, NULL);
}

