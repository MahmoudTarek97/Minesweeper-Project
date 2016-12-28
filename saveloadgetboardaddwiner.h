#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <string.h>

/*----------------------------------addWinner---------------------------------*/
void addWinner()
{
    printf("\n\n    Have you ever won and registered ? Enter <l> to LOGIN \n"
           "    If you are a new player , Enter <r> to REGISTER\n"
           "    If you do not want it , Enter <b> to Back to MAIN MENU\n\n");

    char winnerChoice[500];
    while(1)
    {
        color(10);
        printf("\n    --> Enter Your Choice : ");
        color(15);
        readChoice(winnerChoice,500);
        fflush(stdin);
        if ( (winnerChoice[0] == 'l' || winnerChoice[0] == 'r' || winnerChoice[0] == 'b') && winnerChoice[1]=='\0')
        {
            break;
        }
        else
        {
            color(12);
            printf("\t\t\t\tInvalid Choice !");
            color(10);
        }
    }

    if (winnerChoice[0]=='l')
    {
        int flag=0;
        char winnerName[MAX_LEN];
        while (1)
        {
            printf("   --> Enter your Name : ");
            readName(winnerName,MAX_LEN);
            fflush(stdin);
            if (winnerName[0]!='\0')
                break;
        }

        int i;
        for(i=1;i<=userCounter;i++)
        {
            if(!strcmp(winnerName,user[i].name))    //check if he a registered user
            {                                       //if that true
                flag=1;
                color(11);
                printf("       Your new score has been added to your totalScore , check LEADERBOARD");
                Sleep(1000);
                color(15);
                user[i].totalScore+=score;
                if(score>user[i].highScore)          //he might get a highScore
                    user[i].highScore=score;
                break;
            }
        }
        if (flag==0)
        {
            color(12);
            printf("    \t\t\tWRONG NAME!\n");
            color(15);
            addWinner();
        }
    }

    else if (winnerChoice[0]=='r')
    {
        userCounter++;

        while(1)
        {
            printf("   --> Enter your Name (Max length is 30 Character): ");
            readName(user[userCounter].name,MAX_LEN);
            if (user[userCounter].name[0]!='\0')
                break;
        }
        user[userCounter].highScore=score;
        user[userCounter].totalScore=score;
        color(11);
        printf("       You are added to LEADERBOARD");
        color(15);
        Sleep(1000);
    }
    else if (winnerChoice[0]=='b')
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


    //save new userCounter
    FILE * fc;
    fc = fopen("Data\\userCounter.txt","w");
    fprintf(fc,"%d ",userCounter);
    fc =fclose(fc);

    //sort users by their totalScore
    sortUsers();

    //save updated leaderBoard
    FILE * fu;
    fu = fopen("Data\\usersNames.txt","w");
    //save users names
    int i;
    for(i=1;i<=userCounter;i++)
    {
        fprintf(fu,"%s\n",user[i].name);
    }
    fu =fclose(fu);

    FILE * fs;
    fs = fopen("Data\\usersScores.txt","w");
    //save users scores
    for(i=1;i<=userCounter;i++)
    {
        fprintf(fs,"%f %f\n",user[i].highScore,user[i].totalScore);
    }
    fs =fclose(fs);


}

/*-------------------------------loadGame function----------------------------*/
void loadGame(int gridNum[][MAX_LEN],char gridView[][MAX_LEN],int gridVisited[][MAX_LEN])
{
    //load inputs from file (read it)
    FILE * fp;
    //open file to read it
    fp = fopen("Data\\savedGame.txt","r");

    //read inputs
    fscanf(fp,"%c",&action[0]);
    fscanf(fp,"%d %d",&Rows,&Columns);
    numberOfMines=1+((Rows*Columns)/10);
    fgetc(fp);
    int i=0,j=0;
    for (i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            fscanf(fp,"%c",&gridView[i][j]);
            gridVisited[i][j]=0;
        }
    }
    for (i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            fscanf(fp,"%d",&gridNum[i][j]);
        }
    }
    fscanf(fp,"%d %d",&x,&y);
    fscanf(fp,"%d %d %d %d",&flaggedCells,&numberOfMovements,&check,&savedTimeDiff);

    //close file
    fp =fclose(fp);
}
/*-------------------------------saveGame function----------------------------*/
void saveGame(int gridNum[][MAX_LEN],char gridView[][MAX_LEN],int gridVisited[][MAX_LEN])
{

    //save inputs to file (write it)
    FILE * fp;
    //open file to write in it
    fp = fopen("Data\\savedGame.txt","w");
    //save inputs
    fprintf(fp, "%c %d %d",lastAction,Rows,Columns);
    fprintf(fp,"\n");
    int i,j;
    for (i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            fprintf(fp,"%c",gridView[i][j]);
        }
    }
    fprintf(fp,"\n");
    for (i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            fprintf(fp," %d",gridNum[i][j]);
        }
    fprintf(fp,"\n");
    }
    fprintf(fp,"%d %d",x,y);
    fprintf(fp,"\n%d %d %d",flaggedCells,numberOfMovements,check);
    savedTimeDiff=orgDiff;
    fprintf(fp," %d",savedTimeDiff);
    //close file
    fp =fclose(fp);
}
/*---------------------GetLeaderBoard Function--------------------------------*/
void GetLeaderBoard()
{
    //load userCounter
    FILE * fc;
    fc = fopen("Data\\userCounter.txt","r");
    fscanf(fc,"%d",&userCounter);
    fc =fclose(fc);

    //load users names from file (read it)
    FILE * fu;
    fu = fopen("Data\\usersNames.txt","r");
    int i;
    for(i=1;i<=userCounter;i++)
    {
        char ch='A';
        int j=0;
        while (ch!='\n')
        {
            ch=fgetc(fu);
            user[i].name[j]=ch;
            j++;
        }
        user[i].name[j-1]='\0';
    }
    fu =fclose(fu);

    //load users scores from file (read it)
    FILE * fs;
    fs = fopen("Data\\usersScores.txt","r");
    for(i=1;i<=userCounter;i++)
    {
        fscanf(fs,"%f %f",&user[i].highScore,&user[i].totalScore);
    }
    fs =fclose(fs);
}
/*--------------------debugGrid Function----------------------*/
void debugGrid (int Rows,int Columns,int gridNum[][MAX_LEN])
{
    FILE *fp;
    fp = fopen("Data\\debugGrid.txt","w");
    int i,j;
    i=0;j=0;
    for (i=0;i<Rows;i++)
    {
        for(j=0;j<Columns;j++)
        {
            fprintf(fp,"%5d",gridNum[i][j]);
        }
        fprintf(fp,"\n");
    }
    fp=fclose(fp);
}
