/*---------------------------------printGrid function----------------------------*/
void printGrid(int Rows, int Columns,char gridView[][MAX_LEN]){
    int i=0,j=0;
    orgDiff =TimeDiff+savedTimeDiff;
    int diffInMin = orgDiff/60;
    int diffInSec = orgDiff%60;
    color(14);
    printf("\n\n   HOW TO PLAY ?\n   -----------");
    color(15);
    printf("\n    Enter a symbol of your action then enter cell coordinates\n");
    printf("\n    Available Actions :");
    printf("\n     - Grid Actions\t\t\t- Game Actions");
    printf("\n        * <o> : Open Cell\t\t  * <s> : Save Game");
    printf("\n        * <f> : Flag cell\t\t  * <b> : Back to MAIN MENU");
    printf("\n        * <?> : Mark cell");
    printf("\n        * <u> : Unmark cell\n\n");
    color(14);

    printf("\n\n   THE GAME\n   ---------\n");
    color(15);
    printf("   Your Grid is "); color(13);  printf("%d x %d\t\t\n\n",Rows,Columns); color(15);
    printf("   - There are ");   color(13);  printf("%d ",numberOfMines);   color(15);  printf("Mines.\n");
    printf("   - Flags :"); color(13);  printf(" %d",flaggedCells);   color(15);
    printf("\t\t\t\t- Question Marks : "); color(13); printf("%d\n",markedCells); color(15);
    score = ( pow(Rows,4)* pow(Columns,4) ) /(orgDiff*numberOfMovements);
    printf("   - Score : "); color(13); printf("%-15.3f",score); color(15);
    printf("\t\t- Movements : "); color(13); printf("%d\n",numberOfMovements); color(15);
    printf("   - Time Passed : "); color(13); printf("%0.2d:%0.2d\n\n",diffInMin,diffInSec); color(15);

    printf("%3c",' ');
    for (j=1;j<Columns+1;j++)
        {
            printf(" %3d",j);
        }
    printf("\n  ");
    for (i=0;i<Columns;i++)
    {
        printf("--+-");
    }
    printf("---");
    printf("\n");

    for (i=0;i<Rows;i++)
    {
        printf("%3d ",i+1);
        printf("|");
        for(j=0;j<Columns;j++)
        {
            if (gridView[i][j]=='F') color(10);
            else if (gridView[i][j]=='?') color(14);
            else if (gridView[i][j]=='M') color(11);
            else if (gridView[i][j]=='!') color(12);
            else if (gridView[i][j]=='-') color(13);
            printf("%2c ",gridView[i][j]);
            color(15);
            printf("|");
        }
    printf("\n  ");
    for (j=0;j<Columns;j++)
    {
        printf("--+-");
    }
    printf("---");
    printf("\n");
    }
}


/*--------------------------------youLose function-----------------------------*/
void youLose(int x ,int y,int Rows,int Columns,int gridNum[][MAX_LEN],char gridView[][MAX_LEN])
{
    int i,j;
    for(i=0; i<Rows; i++)
    {
        for(j=0; j<Columns; j++)
        {
           if ( gridView[i][j]=='F' && gridNum[i][j]>=0)
                gridView[i][j]='-';

           else if(gridNum[i][j]==0)
                gridView[i][j]=' ';

           else if(gridNum[i][j]>0)
                gridView[i][j]=gridNum[i][j]+'0';

           else if(gridNum[i][j]<0)
                gridView[i][j]='M';
        }
    }
    gridView[x][y]='!';
}
/*--------------------------------DFS function--------------------------------*/

void DFS(int x,int y,int Rows,int Columns,int gridNum[][MAX_LEN],char gridView[][MAX_LEN],int gridVisited[][MAX_LEN])
{

    if(x-1>=0&&y-1>=0&&gridVisited[x-1][y-1]==0&&gridView[x-1][y-1]!='F')
    {
        if(gridNum[x-1][y-1]==0)
        {
            gridView[x-1][y-1]=' ';
            gridVisited[x-1][y-1]=1;
            DFS(x-1,y-1,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else  if(gridNum[x-1][y-1]>0){
            gridView[x-1][y-1]=gridNum[x-1][y-1]+'0';
        }
    }


     if(x-1>=0&&gridVisited[x-1][y]==0&&gridView[x-1][y]!='F')
    {
        if(gridNum[x-1][y]==0)
        {
            gridView[x-1][y]=' ';
            gridVisited[x-1][y]=1;
            DFS(x-1,y,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x-1][y]>0)
            gridView[x-1][y]=gridNum[x-1][y]+'0';
    }


    if(x-1>=0&&y+1<Columns&&gridVisited[x-1][y+1]==0&&gridView[x-1][y+1]!='F')
    {
        if(gridNum[x-1][y+1]==0)
        {
            gridView[x-1][y+1]=' ';
            gridVisited[x-1][y+1]=1;
            DFS(x-1,y+1,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x-1][y+1]>0)
            gridView[x-1][y+1]=gridNum[x-1][y+1]+'0';
    }


    if(y-1>=0&&gridVisited[x][y-1]==0&&gridView[x][y-1]!='F')
    {
        if(gridNum[x][y-1]==0)
        {
            gridView[x][y-1]=' ';
            gridVisited[x][y-1]=1;
            DFS(x,y-1,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x][y-1]>0)
             gridView[x][y-1]=gridNum[x][y-1]+'0';
    }


    if(y+1<Columns&&gridVisited[x][y+1]==0&&gridView[x][y+1]!='F')
     {
         if(gridNum[x][y+1]==0)
         {
            gridView[x][y+1]=' ';
            gridVisited[x][y+1]=1;
            DFS(x,y+1,Rows,Columns,gridNum,gridView,gridVisited);
        }
         else if(gridNum[x][y+1]>0)
            gridView[x][y+1]=gridNum[x][y+1]+'0';
     }


    if(x+1<Rows&&y-1>=0&&gridVisited[x+1][y-1]==0&&gridView[x+1][y-1]!='F')
    {
        if(gridNum[x+1][y-1]==0)
        {
            gridView[x+1][y-1]=' ';
            gridVisited[x+1][y-1]=1;
            DFS(x+1,y-1,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x+1][y-1]>0)
            gridView[x+1][y-1]=gridNum[x+1][y-1]+'0';
    }


    if(x+1<Rows&&gridVisited[x+1][y]==0&&gridView[x+1][y]!='F')
    {
       if(gridNum[x+1][y]==0)
        {
            gridView[x+1][y]=' ';
            gridVisited[x+1][y]=1;
            DFS(x+1,y,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x+1][y]>0)
            gridView[x+1][y]=gridNum[x+1][y]+'0';
    }


    if(x+1<Rows&&y+1<Columns&&gridVisited[x+1][y+1]==0&&gridView[x+1]

[y+1]!='F')
    {
       if(gridNum[x+1][y+1]==0)
        {
            gridView[x+1][y+1]=' ';
            gridVisited[x+1][y+1]=1;
            DFS(x+1,y+1,Rows,Columns,gridNum,gridView,gridVisited);
        }
        else if(gridNum[x+1][y+1]>0)
            gridView[x+1][y+1]=gridNum[x+1][y+1]+'0';
    }
}
/*--------------------------------valuedCell function-------------------------*/
void valuedCell(int x,int y,int Rows,int Columns,int gridNum[][MAX_LEN],char gridView[][MAX_LEN])
{
    if(gridNum[x][y]==0)
        gridView[x][y]==' ';
    else
        gridView[x][y]=gridNum[x][y]+'0';
}
/*--------------------------------flagsArCell function------------------------*/
int flagsArCell(int x ,int y,int Rows ,int Columns,char gridView[][MAX_LEN]){
    int flags=0;

    if(x-1>=0 && y-1>=0 &&gridView[x-1][y-1]=='F')
        flags++;

    if(x-1>=0&&gridView[x-1][y]=='F')
        flags++;

    if(x-1>=0 && y+1<Columns && gridView[x-1][y+1]=='F')
        flags++;

    if(y-1>=0 && gridView[x][y-1]=='F')
        flags++;

    if(y+1<Columns && gridView[x][y+1]=='F')
        flags++;

    if(x+1<Rows && y-1>=0 && gridView[x+1][y-1]=='F')
        flags++;

    if(x+1<Rows && gridView[x+1][y]=='F')
        flags++;

    if(x+1<Rows && y+1<Columns && gridView[x+1][y+1]=='F')
        flags++;

    return flags;
    }
/*-----------------------------openCell Function------------------------------*/

void openCell(int A,int B,int Rows, int Columns,char gridView[][MAX_LEN],int gridNum[][MAX_LEN],int gridVisited[][MAX_LEN])
{
    if(gridNum[A][B]<0)
    {
        youLose(A,B,Rows,Columns,gridNum,gridView);
        lose = 1;
    }

    else if(gridNum[A][B]==0)
    {
        DFS(A,B,Rows,Columns,gridNum,gridView,gridVisited);
    }

    else if(gridNum[A][B]>0)
    {
        valuedCell(A,B,Rows,Columns,gridNum,gridView);
    }
    if ( (lose==0) && (winCounter(Rows,Columns,gridNum,gridView) == ( (Rows*Columns)-numberOfMines) ) )
    {
        //youwin
        win=1;
        int i,j;
        for(i=0;i<Rows;i++)
        {
            for(j=0;j<Columns;j++)
            {
                if(gridNum[i][j]<0)
                    gridView[i][j]='F';
            }
        }
    }
}
/*--------------------------------winCounter function-------------------------*/
int winCounter(int Rows,int Columns,int gridNum[][MAX_LEN],char gridView[][MAX_LEN])
{
    int Counter=0;
    int i,j;
    for(i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            if (gridNum[i][j]>=0 && (gridView[i][j]==' ' || (gridView[i][j]>'0' && gridView[i][j]<='8') ) )
                Counter++;
        }
    }
    return Counter;
}
