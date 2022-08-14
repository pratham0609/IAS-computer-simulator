//CA Assignment: Pratham Dandale - IMT2020038
//               Prabal Mahajan  - IMT2020514  

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void fetch(char*,char*,char*[]);          
void execute(char*,char *,char* []);    
char* substring(char *, const char *, int  a, int n);
int convertBtoD(int n);  //binary to decimal           
int power(int a,int b);         

int PC=6;
int MAR;
int HALT=0;// HALT
char AC[10];
char IBR[40];

void fetch(char*MBR,char*IR,char**memory)
{
    char a[12];
    if( strcmp(IBR,"") != 0)       // When there is instruction in IBR.
    { 
        substring(IR,IBR,0,8);
        substring(a,IBR,8,12);
        MAR = convertBtoD(atoi(a)); // MAR Decimal value.
        PC = PC+1;
        strcpy(IBR,"");
    }
    else                            // When IBR has no instruction.
    { 
        MAR = PC;
        *memory = *(memory+MAR);
        strcpy(MBR,*memory);
        char b[25]; 
        strcpy(b,"");
        substring(b,MBR,0,20);
        if( strncmp(b,"00000000000000000000",20) == 0)  
        // When there is no right instruction.
        { 
            substring(IR,MBR,20,8);
            substring(a,MBR,28,12);
            MAR = convertBtoD(atoi(a));
            PC = PC+1;
        }
        else 
        { 
            // Check if L instruction is there or not assigned "all 0s" for no instruction.
            substring(IBR,MBR,20,20);
            substring(IR,MBR,0,8);
            substring(a,MBR,8,12);
            MAR = convertBtoD(atoi(a));
        }
    }
}

void execute(char*IR,char *MBR,char** memory) 
{ 
	printf("%s",IR);
    if( strncmp(IR,"00001010",8) == 0)// Load M(X)
	{ 
        *memory = *(memory+MAR);
        strcpy(MBR,*memory);
        strcpy(AC,MBR);
        printf("%s"," --> LOAD");
        printf("\n");
    } 
    else if(( strncmp(IR,"00100001",8)) == 0) // Store M(X)
    {
        *memory = *(memory+MAR);
        strcpy(MBR,AC);
        strcpy(*memory,MBR);
        printf("%s"," --> STORE");
        printf("\n");

    } 
    else if(( strncmp(IR,"00001101",8)) == 0)// Jump M(X,20:39) if nonnegative
    { 
        *memory = *(memory+MAR);
        strcpy(MBR,*memory);
        if(atoi(AC)<=0)
        {     
            printf("%s"," --> NO JUMP");
            printf("\n");
        }
        else
        {
        	char a[20];
            *memory = *(memory+MAR);
            substring(IBR,*memory,20,40);
            PC = MAR;
            printf("%s"," --> JUMP");
            printf("\n");
        }
    }
    else if(( strncmp(IR,"00000101",8)) == 0)
    { 

        *memory = *(memory+MAR);
        strcpy(MBR,*memory);
        
        sprintf(AC,"%d",(atoi(AC) + atoi(MBR)));    // Add M(X) and store to AC.
        printf("%s"," --> ADD");
        printf("\n");
    }
    else if(( strncmp(IR,"00000110",8)) == 0)
    { 
        *memory = *(memory+MAR);
        strcpy(MBR,*memory);
        sprintf(AC,"%d",(atoi(AC) - atoi(MBR)));   // Subtract M(X) store to AC.
        printf("%s"," --> SUBTRACT");
        printf("\n");
    }
    else if(( strcmp(IR,"00010100")) == 0)
    { 

        sprintf( AC, "%d" , 2*atoi(AC) );
        printf("%s"," --> LSH");
        printf("\n");
    }
    else if(( strcmp(IR,"00010101")) == 0)//RSH Divide by 2.

    { 
        sprintf(AC,"%d",atoi(AC)/2);
        printf("%s"," --> RSH");
        printf("\n");
    }
    else if((strncmp(IR,"11111111",8))==0)// HALT stop the excecution.
    {
        HALT=1;
        printf("%s"," --> HALT");
        printf("\n");
    }
}

char* substring(char *substr, const char *source, int beg, int n)// Returns Substring from a given string.
{
    while (n > 0)
    {
        *substr = *(source + beg);
        substr++;
        source++;
        n--;
    }
    *substr = '\0';//terminate substring

    // return the substring
    return substr;
}
int convertBtoD(int n) //Decimal to Binary
{
    int dec = 0, i = 0, rem;
    while (n != 0) 
    {
        rem = n % 10; n /= 10;
        dec += rem * power(2, i);
        ++i;
    }
    return dec;
}
int power(int base, int exponent) 
{
    int ans=1;
    for (exponent; exponent>0; exponent--)
        ans = ans * base;
    return ans;
}

int main()
{
    char **memory; 
    memory = (char **) malloc(1000 * sizeof(char*));
    int row=0;  
    while (row < 1000){
      memory[row] = (char *) malloc(40 * sizeof(char));
      row++;
    }
    char MBR[40];
    char IR[8];
       
    //Instructions for PC = 0
    
    memory[0] = "0000110100000000010000001010000000001101";
    memory[1] = "0000101000000000110100000110000000001110";
    memory[2] = "0000010100000000111000100001000000001111";
    memory[3] = "1111111100000000000000100001000000001111";
    memory[4] = "0000000000000000000000100001000000001111";
    memory[5] = "1111111100000000000000100001000000001111";
    
    //Data
    memory[13] = "6";//a
    memory[14] = "12";//b 
    /*Memory[15] consists of output*/
    
    //Instructions for PC = 6 
    
    memory[6] = "0000101000000001000000000110000000010001";
    memory[7] = "0000110100000000101000001010000000010000";
    memory[8] = "0001010000000000000000100001000000010010";
    memory[9] = "1111111100000000000000100001000000001111";
    memory[10] = "0000000000000000000000001010000000010001";
    memory[11] = "0001010100000000000000100001000000010010";
    memory[12] = "1111111100000000000000000000000000000000";
    
    // Data
    memory[16] = "7";//a
    memory[17] = "4";//b 
    /* Memory[18] consists of the output*/
    
    strcpy(IBR,"");
    while(1)
    {
        fetch(MBR,IR,memory);
        execute(IR,MBR,memory);
        if(HALT==1) 
            break;
    }
    printf("%s","OUTPUT --> " );
    printf("%s",memory[18] );
    return 0;
}
