#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int sd,cadl;
    struct sockaddr_in sad,cad;
    char str[50];

    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    sad.sin_port=htons(9996);
    connect(sd,(struct sockaddr*)&sad,sizeof(sad));
    
    recv(sd,str,sizeof(str),0);
    printf("server says: %s\n",str);
    close(sd);
    return 0;
}