#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 1000
#define Size 100
#define s 50
void idSort(int [],char [][s], double [],int);
void nameSort(int [],char [][s], double [],int);
void scoresSort(int [],char [][s], double [],int);
void idsearch(int [],char name[][s], double [],int);
void namesearch(int [],char [][s], double [],int);
void fprints(int [],char [][s], double [],int);
void change(int [],char [][s], double [],int,int);
void printTable(int [],char [][s], double [],int);
int main()
{
    int ID[size],j,i=0,choice;
    char *token, name[size][s],get [size][Size],fname[s];
    double test,t, sum=0,scores[size];
    FILE *in;
    do                                                                                           // this loop for take Existing file and i use do to don't take value before loop
    {
        printf("Enter file name: ");
        gets(fname);
        in = fopen(fname, "r");
        if(in == NULL)
            printf("The file %s can NOT open\n\n",fname);
    }
    while(in == NULL);

    do                                                                                          //loop for end of file to take all data and i use do to don't take value before loop
    {
        fgets(get[i], Size, in);
        if(feof(in))
            break;
        token = strtok(get[i],"$");

        ID[i] = atoi(token);                                                                    //atoi is function for take ascii then make it integer and save as id
        if(atof(token)<1000000 || atof(token)>9999999)                                          //for cheak if the ides have error
        {
            printf("There are an error in line %d The id could not be %d\n",i+1,atoi(token));   //print line of error
            j=7;                                                                                // to select there are error in next step
            break;
        }
        token = strtok(NULL,"$");
        strcpy(name[i],token);                                                                  // store name of student
        j=1;
        sum=0;
        while(token != NULL)
        {
            token = strtok(NULL,"$");
            test = atof(token);
            if(test>100 || test<0)                                                            //for cheak if the grades have error
            {
                printf("There are an error in line %d (in grades)\n",i+1);                    //print line of error
                break;
                j=7;                                                                          // to select there are error in next step
            }
            if(j==1 || j == 2 )
                t=0.15;
            else if(j==3)
                t=0.25;
            else if(j==4)
                t=0.1;
            else if(j==5)
                t=0.35;
            else
                break;
            test *= t;
            sum+=test;
            ++j;                                                                            // count number of grade to print error if greater or less than 5
        }
        if(j==6)                                                                            // when end Previous step we find j=6 because there are 5 grades and the loop is add one after take all of them
            scores[i] = sum;                                                                // store sum of Calculate grades
        ++i;
    }
    while(!feof(in));


    if(j==6)                                                                                // if j =6 that mean the data is true (in 42 and 57 I take it to 7 (when we have error)
        do                                                                                  // loop for keep displaying the menu until the user select exit (number 6)
        {
            printf("______________________________________________________________\n1) Sort data in ascending order according to student's IDs and then display it.\n");
            printf("2) Sort data in ascending order according to student's names and then display it.\n");
            printf("3) Sort data in descending order according to student's scores and then display it.\n");
            printf("4) Ask the user to enter a student ID and display his score.\n");
            printf("5) Ask the user to enter a student name and display his score.\n");
            printf ("6) Exit the program.\n");
            printf("\nenter a choice from Previous menu: ");
            scanf("%d",&choice);
            switch (choice)                                                                 // switch for do function that make the number from the menu
            {
            case 1:
                idSort(ID,name,scores,i);
                break;
            case 2:
                nameSort(ID,name,scores,i);
                break;
            case 3:
                scoresSort(ID,name,scores,i);
                break;
            case 4:
                idsearch(ID,name,scores,i);
                break;
            case 5:
                namesearch(ID,name,scores,i);
                break;
            case 6:
                break;
            default:
                printf("you enter undefined number\n");                                   // for print error if you enter number that not find in menu
            }
        }
        while(choice != 6);

    printf("\nThank you, give me a bonus.");
    fclose(in);
    return 0;
}

void idSort(int ID[],char name[][s], double scores[],int n)
{
    int i,j,flag;
    printf("\ndata in ascending by student's IDs\n");
    for(i=0 ; i<n ; i++)                                                                // two loop for sort
        for(j=0 ; j<n ; ++j)
            if(ID[j]>ID[i])                                                             // compare by ID to sort by it
                change(ID,name,scores,i,j);                                             // function for change id[i] and id[j] and names and scores

    printTable(ID,name,scores,n);                                                       // function for print all of arrays

    printf("do you want to save change?\n1)yes\n2)no\nenter number of choice: ");
    scanf("%d",&flag);
    while(flag != 1 && flag != 2)                                                       // loop for if the user enter a number that is not 1 or 2
    {
        printf("you enter undefined number please enter 1 or 2: ");
        scanf("%d",&flag);
    }
    if(flag == 1)
        fprints(ID,name,scores,n);

}

void nameSort(int ID[],char name[][s], double scores[],int n)
{
    int i,j,flag;
    printf("\ndata in ascending by student's names\n");
    for(i=0 ; i<n ; i++)
    {
        for(j=0 ; j<n ; ++j)
            if(strcmp(name[j],name[i])>0)                                           // compare by name to sort by it
                change(ID,name,scores,i,j);

    }

    printTable(ID,name,scores,n);

    printf("do you want to save change?\n1)yes\n2)no\nenter number of choice: ");
    scanf("%d",&flag);
    while(flag != 1 && flag != 2)                                                   // loop for if the user enter number else 1 or 2
    {
        printf("you enter undefined number please enter 1 or 2: ");
        scanf("%d",&flag);
    }
    if(flag == 1)
        fprints(ID,name,scores,n);                                                 // call function for print in file
}

void scoresSort(int ID[],char name[][s], double scores[],int n)
{
    int i,j,flag;
    printf("\ndata in descending by student's scores\n");
    for(i=0 ; i<n ; i++)
        for(j=0 ; j<n ; ++j)
            if(scores[j]<scores[i])                                               // compare by scores to sort by it
                change(ID,name,scores,i,j);

    printTable(ID,name,scores,n);

    printf("do you want to save change?\n1)yes\n2)no\nenter number of choice: ");
    scanf("%d",&flag);
    while(flag != 1 && flag != 2)
    {
        printf("you enter undefined number please enter 1 or 2: ");
        scanf("%d",&flag);
    }
    if(flag == 1)
        fprints(ID,name,scores,n);
}

void idsearch(int ID[],char name[][s], double scores[],int n)
{
    int id,i,flag=0;                                                                // flag for print if there is no student with the id that the user enter it
    printf("Enter ID of student to show his score: ");
    scanf("%d",&id);
    for(i=0 ; i<n ; i++)
        if(ID[i] == id)                                                            // if the id موجود in the file make the flag to one to print it
        {
            flag=1;
            break;
        }

    if(flag)
        printf("\nThe score of %d is: %.2f\n",id,scores[i]);
    else
        printf("There is NO student with the number %d in the file\n",id);

}

void namesearch(int ID[],char name[][s], double scores[],int n)
{
    int i,flag=0;
    char key[s];
    printf("Enter a name of student to show his score: ");
    fflush(stdin);                                                                 // for fix the problem that take press enter as string
    gets(key);
    for(i=0 ; i<n ; i++)
        if(strcmp(name[i],key)==0)
        {
            flag=1;
            break;
        }

    if(flag)
        printf("\nThe score of %s is: %.2f\n",key,scores[i]);
    else
        printf("\nThere is NO student with the name %s in the file\n",key);
}


void change(int ID[],char name[][s], double scores[],int i,int j)                   // function for change the ides and names and scores
{
    int temp;
    char temp1[s];
    double temp2;
    temp = ID[j];
    ID[j]=ID[i];
    ID[i]=temp;
    strcpy(temp1,name[j]);
    strcpy(name[j],name[i]);
    strcpy(name[i],temp1);
    temp2 = scores[j];
    scores[j] = scores[i];
    scores[i] = temp2;
}

void printTable(int ID[],char name[][s], double scores[],int n)                     // function for print the table of student
{
    int i;
    printf("ID");                                                                   // this line and 251 and 252 for (الترتيب)
    printf("              name");
    printf("                                                            score\n");
    for( i=0 ; i<n ; i++)
    {
        printf("%d\t\t", ID[i]);
        printf("%-50s\t\t",name[i]);                                                // %-50s for (حجز مساحة) in memory to (الترتيب) and - for print from left to right
        printf("%.2f\n",scores[i]);
    }
    printf("\n");
}

void fprints(int ID[],char name[][s], double scores[],int n)                        // function for print the table of student in file that we enter the name of it
{
    int i;
    char fname[s];
    FILE *out;
    printf("enter file name: ");
    fflush(stdin);                                                                  // for fix the problem that take press enter as string
    gets(fname);

    out = fopen(fname, "w");
    fprintf(out,"ID");
    fprintf(out,"              name");
    fprintf(out,"                                                            score\n");
    for( i=0 ; i<n ; i++)
    {
        fprintf(out,"%d\t\t", ID[i]);
        fprintf(out,"%-50s\t\t",name[i]);
        fprintf(out,"%.2f\n",scores[i]);
    }
    fprintf(out,"\n");
}
