#include <stdio.h>
#include <stdlib.h>

int singleTest(void);

void multipleTest(void);

void fileTest(void);

int main()
{
    printf("Hello World!\n");
    multipleTest();
    fileTest();
    return 0;
}

int singleTest(void){

    int pass=0;
    int expectedInt = 5;
    int Result = 3+2;
    //float expectedFloat;
    //char expectedChar;
    //int stringSize;
    //char expectString[stringSize];
    //Insert your function
    if(Result == expectedInt)pass=1;

    return pass;
}

void multipleTest(void){
    char ans,foo;
    int num=0;
    printf("Do you want to run a test? Press y for yess, n for no, then enter key \n y/n? \n");

    do{
        ans=getchar();
        if(ans!='y' && ans!='n')printf("Incorrect input. Try again\n");
        do{
            foo=getchar();
        }while(foo!='\n');
    }while(ans!='y' && ans!='n');

    while(ans=='y'){
        num++;
        if(singleTest()==1){
            printf("Test %d",num);
            printf(" Passed\n");
            printf("Do you want to run another test? Press y for yess, n for no, then enter key \n y/n? \n");
            do{
                ans=getchar();
                if(ans!='y' && ans!='n')printf("Incorrect input. Try again\n");
            }while(ans!='y' && ans!='n');
            do{
                foo=getchar();
            }while(foo!='\n');
        }
    }

}

void fileTest(void){
    FILE *myFile;
    myFile = fopen("floatVals.txt", "rb");

    //read file into array
    int numberArray[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        fscanf(myFile, "%d,", numberArray[i]);
    }

    for (i = 0; i < 5; i++)
    {
        printf("Number is: %d\n\n", numberArray[i]);
    }
}



