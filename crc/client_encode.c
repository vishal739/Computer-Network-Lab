#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int sd,dl,divl,i,j;
    char data[100],data1[100],divisor[100];
    struct sockaddr_in sad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9993);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd,(struct sockaddr*)&sad,sizeof(sad));

    printf("Enter bitstream :");
    scanf("%s",data);
    printf("Enter Coefficient: ");
    scanf("%s",divisor);
    dl=strlen(data);
    divl=strlen(divisor);
    for(int i=dl;i<dl+(divl-1);i++){
        data[i]='0';
    }
    data[dl+(divl-1)]='\0';
    strcpy(data1,data);
    printf("Update codeword is: %s\n",data1);
    for(int i=0;i<dl;i++){
        if(data1[i]=='1'){
            for(int j=0;j<divl;j++){
                if(data1[i+j]==divisor[j]){
                    data1[i+j]='0';
                }else{
                    data1[i+j]='1';
                }
            }
        }
    }
    printf("data1 : %s\n",data1);
    for(int i=dl;i<dl+(divl-1);i++){
        data[i]=data1[i];
    }
    
    printf("Codeword after encoding: %s\n",data);
    send(sd,data,sizeof(data),0);
    send(sd,divisor,sizeof(divisor),0);
    close(sd);
}