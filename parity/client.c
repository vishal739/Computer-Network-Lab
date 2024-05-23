#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int sd,bit;
    char str[50];
    struct sockaddr_in sad;
    sd= socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family= AF_INET;
    sad.sin_port=htons(9995);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd,(struct sockaddr*)&sad,sizeof(sad));

    recv(sd,str,sizeof(str),0);
    recv(sd,&bit,sizeof(bit),0);
    int len=strlen(str);
    printf("bitstream recieved:  %s\n",str);
    int count=0;
    for(int i=0;i<len;i++){
        if(str[i]=='1') count++; 
    }
    if(bit==1){
        if(count%2==0){
            printf("No error found in even parity check");
        }else{
            printf("error found in even parity check");
        }
    }else{
        if(count%2==1){
            printf("No error found in odd parity check");
        }else{
            printf("error found in odd parity check");
        }
    }
    close(sd);
}