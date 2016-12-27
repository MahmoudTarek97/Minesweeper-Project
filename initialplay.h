/*-------------------------------gameGenerate Function-------------------------*/
void generateMines(int Rows,int Columns,char gridView[][MAX_LEN],int
gridNum[][MAX_LEN],int x,int y){
    int i=0;
    srand(time(0));   // generate random mine
    while(i<numberOfMines)
    {
        int rx=rand()%(Rows);
        int ry=rand()%(Columns);
        if((gridNum[rx][ry]<0)||(rx==x&&ry==y))
        {
            continue;       // there is a mine in cell or it is first move for player so we don't put mine
        }
        else
        {      // put a mine
            gridNum[rx][ry]= -10;
            calculateNearby(rx,ry,Rows,Columns,gridNum);       // this function to calculate the value of nearby mine
            i++;
        }
    }
}

/*--------------------------------calculateNearby function---------------------*/
int calculateNearby(int rx,int ry,int Rows,int Columns,int gridNum[][MAX_LEN])  //calculate the value of nearby mine
{
    if(rx-1>=0 && ry-1>=0 && gridNum[rx-1][ry-1]>=0)
        gridNum[rx-1][ry-1]++;

    if(rx-1>=0 && gridNum[rx-1][ry]>=0)
        gridNum[rx-1][ry]++;

    if(rx-1>=0 && ry+1<Columns && gridNum[rx-1][ry+1]>=0)
        gridNum[rx-1][ry+1]++;

    if(ry-1>=0 && gridNum[rx][ry-1]>=0)
        gridNum[rx][ry-1]++;

    if(ry+1<Columns && gridNum[rx][ry+1]>=0)
        gridNum[rx][ry+1]++;

    if(rx+1<Rows && ry-1>=0 && gridNum[rx+1][ry-1]>=0)
        gridNum[rx+1][ry-1]++;

    if(rx+1<Rows && gridNum[rx+1][ry]>=0)
        gridNum[rx+1][ry]++;

    if(rx+1<Rows && ry+1<Columns && gridNum[rx+1][ry+1]>=0)
        gridNum[rx+1][ry+1]++;
}
/*---------------------------------initializeGrid function-------------------------*/
void initializeGrid(int Rows, int Columns,char gridView[][MAX_LEN],
                    int gridNum[][MAX_LEN],int gridVisited[][MAX_LEN]){
    int i=0,j=0;
    for (i=0;i<Rows;i++)
        {
            for(j=0;j<Columns;j++)
            {
                gridView[i][j]='X';
                gridNum[i][j]=0;
                gridVisited[i][j]=0;
            }
        }
    }
