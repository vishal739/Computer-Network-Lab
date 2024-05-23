#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


int main() {

    //sender
    char input[100];
    int data1[100], codeWord[100];
    int i,j,k,l,c,r,dl,z;

    printf("Enter the data: ");
    scanf("%s",&input);

    dl=strlen(input);
    //Formula 2^k>=m+k+1
    for(i=0;pow(2,i)<dl+i+1;i++){}

    r=i;
    //Converting the data into int
    for(i=0;i<=dl;i++){
        data1[i]=input[i]-48;
    }

    //creating the codeword with 999 in parity index
    k=0;
    for(i=1,j=dl-1;i<=dl+r;i++){
        if(i==pow(2,k)){
            codeWord[i]=999;
            k++;
        }
        else{
            codeWord[i]=data1[j];
            j--;
        }
    }

    k=0;
    for(i=0;i<r;i++){
        z=pow(2,i);
        //1 counter
        c=0;
        //j=z+k setting next occurrence of the no
        for(j=z;j<=dl+r;j=z+k){
            //k<z+j upto the number will occur 4+4=8, 4+8=12
            for(k=j;k<z+j;k++){
                if(k<=r+dl){
                    if(codeWord[k]!=999)
                        c=c+codeWord[k];
				}
            }
        }
        codeWord[z]=c%2;
    }

    for(i=dl+r;i>0;i--){
        printf("%d",codeWord[i]);
    }

    //receiver
    char receiverInput[100];
    int rdata1[100], rdata2[100];

    printf("\nEnter the data in receiver end");
    scanf("%s", &receiverInput);

    dl=strlen(receiverInput);

    for(i=0;pow(2,i)<dl+1;i++){}

    r=i;
    //Converting the data and reversing
    for(i=1,j=dl-1;i<=dl;i++,j--){
        rdata1[i]=receiverInput[j]-48;
    }

    //checking
    l=1;
    rdata2[0]=0;
    for(i=0;i<r;i++){
        z=pow(2,i);
        c=0;
        for(j=z;j<=dl;j=z+k){
            for(k=j;k<z+j;k++){
                if(k<=dl){
                    c=c+rdata1[k];
                }
            }
        }
        rdata2[l]=c%2;
        rdata2[0]=rdata2[0]+rdata2[l];
        l++;
    }

    for(i=0;i<=r;i++){
        printf("%d ",rdata2[i]);
    }

    if(rdata2[0]==0){
        printf("\nData has no error \n");
    }
	else{
        printf("\nData has error \n");
        j=0;
        //Finding the position of error
        for(i=1;i<=r;i++)
        {
            if(rdata2[i]==1)
                j=j+pow(2,(i-1));
        }

        printf("Error is at position %d\n",j);
        if(rdata1[j]==0)
            rdata1[j]=1;
        else
            rdata1[j]=0;
        printf("Corrected codeword is: ");
        for(i=dl;i>0;i--)
            printf("%d ",rdata1[i]);
        printf("\n");
    }

	return 0;
}
