#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int sd,cd,i,j,dl,divl;
    char data[100],data1[100],divisor[100];
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(9993);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd,(struct sockaddr*)&sad,sizeof(sad));
    listen(sd,10);
    int cadl=sizeof(cad);
    cd=accept(sd,(struct sockaddr*)&cad,&cadl);
    recv(cd,data,sizeof(data),0);
    recv(cd,divisor,sizeof(divisor),0);
    printf("Recieved Codeword : %s\n",data);
    printf("Recieved Coefficient: %s\n",divisor);
    dl=strlen(data);
    divl=strlen(divisor);
    strcpy(data1,data);
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
    int flag=0;
    for(int i=0;i<strlen(data1);i++){
        if(data1[i]=='1'){
            printf("Error in recieved data");
            flag=1;
            break;
        }
    }
    data[dl-(divl-1)]='\0';
    if(flag==0){
        printf("No error in recived data: %s\n",data);
    }

    close(sd);
    close(cd);
   
}