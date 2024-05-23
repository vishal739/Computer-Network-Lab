#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, dl, divl;
    char data[100], data1[100], divisor[100];
    printf("Enter bitstream: ");
    scanf("%s", data);
    printf("Enter coefficient: ");
    scanf("%s", divisor);
    dl = strlen(data);
    divl = strlen(divisor);
    for (int i = dl; i < dl + divl - 1; i++)
    {
        data[i] = '0';
    }
    data[dl + divl - 1] = '\0';
    printf("update data is: ");
    for (int i = 0; i < dl + divl - 1; i++)
    {
        printf("%c ", data[i]);
    }
    strcpy(data1, data);
    for (int i = 0; i < dl; i++)
    {
        if (data1[i] == '1')
        {
            for (int j = 0; j < divl; j++)
            {
                if (data1[i + j] == divisor[j])
                {
                    data1[i + j] = '0';
                }
                else
                {
                    data1[i + j] = '1';
                }
            }
        }
    }
    for (int i = dl; i < dl + (divl - 1); i++)
    {
        data[i] = data1[i];
    }
    printf("\ncodeword data is: %s\n",data);
    
    printf("\n");
    
    //Decode part
    int rdl = strlen(data);
    strcpy(data1, data);
    for (int i = 0; i < rdl; i++)
    {
        if (data1[i] == '1')
        {
            for (int j = 0; j < divl; j++)
            {
                if (data1[i + j] == divisor[j])
                {
                    data1[i + j] = '0';
                }
                else
                {
                    data1[i + j] = '1';
                }
            }
        }
    }
    printf("data after %d div: %s\n",rdl,data1);
    int flag=0;
    for(int i=0;i<strlen(data1);i++){
        if(data1[i]=='1'){
            printf("Error in data recieved %s \n",data1);
            flag=1;
            break;
        }
    }
    data[rdl-(divl-1)]='\0';
    if(flag==0){
        printf("No error in codeword %s\n",data);
    }
}