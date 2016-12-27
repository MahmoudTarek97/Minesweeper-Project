#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN 30
struct user{
    char name[MAX_LEN];
    float highScore;
    float totalScore;
}user[MAX_LEN];

int userCounter=0;
int startTime=0,endTime=0,TimeDiff=0,savedTimeDiff=0,orgDiff;
int lose=0;
int win=0;
int numberOfMines;
int numberOfMovements = 0;
double score = 0;
int flaggedCells = 0;
int markedCells = 0;
char action[MAX_LEN];
int x,y;
int check=0;
char lastAction;
int firstWelcome=0;
int Rows,Columns;
int i=0;
int j=0;
int ssd=0;
time_t initial_t;
int yu=0;
