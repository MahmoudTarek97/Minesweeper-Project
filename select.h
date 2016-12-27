
/*----------------------------------readName function---------------------------*/
void readName(char str[], int n)
{
    int ch, i=0,j;
    int spacecounter=0;
    while( (ch=getchar()) != '\n' && i<n)
    {
        if((i==0 && (ch ==' ' || ch =='\t')) ||
          ((str[i-1] ==' ' || str[i-1]=='\t') && (ch==' ' ||ch=='\t') && spacecounter>0))
            continue;
        else
        {
            if (ch=='\t')
                ch=' ';

            str[i]=ch;
            if (ch==' ')
                spacecounter++;
            i++;
        }
    }
    if (str[i-1]==' ')
        i--;
    str[i]='\0';

    for(j=0;j<i;j++)
    {
        //Convert All Capital Letters (if exists) to Small Letters
        if (str[j]>=65 && str[j]<=90)
                str[j]+=32;
    }
}
/*--------------------------------readChoice function---------------------------*/
void readChoice(char str[], int n)
{
    int ch, i=0;
    while( (ch=getchar()) != '\n' && i<n)
    {
        if(ch==' ' || ch=='\t')
            continue;
        else
        {
            str[i]=ch;
            i++;
        }
    }
    str[i]='\0';
}
/*---------------------------------Selection function---------------------------*/
int Selection(){
    char choice[500];
    choice[0]='0';
    while (1)
    {
        color(10);
        printf("\n   --> Enter the number of your selection (1,2,3,4,5) : ");
        color(15);
        readChoice(choice,500);
        fflush(stdin);
        color(15);
        printf("\a");
        if ((choice[0] =='1' || choice[0] =='2' || choice[0] =='3' || choice[0] =='4' ||choice[0] =='5') && choice[1]=='\0')
            break;
        else
        {
            color(12);
            printf("\t\t\t\t\t\t\t\tWRONG SELECTION !");
            color(15);
        }
    }
        if (choice[0] == '1')
            return 1;
        if (choice[0] == '2')
            return 2;
        if (choice[0] == '3')
            return 3;
        if (choice[0] == '4')
            return 4;
        if (choice[0] == '5')
            return 5;
    }
    /*----------------------------------numberValue function--------------------*/
int numberValue(char str[],int n,int k)
{
    int value;
    if (k==1)
    {
        value = str[0]-'0';
    }
    else if (k==2)
    {
        value = (str[0]-'0')*10 + (str[1]-'0');
    }
    return value;
}
/*----------------------------------lazyUserInput-------------------------------*/
void lazyUserInput(int timerr,char action[MAX_LEN]){
    ssd=0;
    readChoice(action,MAX_LEN);
    ssd=1;
    time(&initial_t);
    int xp,yp;      getCurrentPosition(&xp,&yp);
    gotoPosition(0,0);
    printf("\t\t\t\t\t\t\t");
    gotoPosition(xp,yp);
}
    /*----------------------------numberCheck function--------------------------*/

int numberCheck(char str[],int n)
{
    /*this function return 0 if it is invaild number , Validity range (2-->30)
                           1 if it is 1 digit number
                           2 if it is 2 digits number*/
    //is it 1 digit number ?
    if(str[1]=='\0')
    {
        if (str[0]>='2' && str[0]<='9')
            return 1;
    }
    else if(str[2]=='\0')
    {
        //it is 2 digits number
        //check for 1st digit
        if (str[0]=='1' || str[0]=='2')
        {
            //check for 2nd digit
            if (str[1]>='0' && str[1]<='9')
                return 2;
        }
        else if (str[0]=='3')
        {
            if (str[1]=='0')
                return 2;
        }
    }
    else
        return 0;
}
