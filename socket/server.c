#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main(){
    int sd,cd,cadl;
    struct sockaddr_in sad,cad;
    char str[50];
    sd =socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family= AF_INET;
    sad.sin_port= htons(9996);
    sad.sin_addr.s_addr= inet_addr("127.0.0.1");
    

    bind(sd,(struct sockaddr*)&sad,sizeof(sad));
    listen(sd, 10);
    cadl= sizeof(cad);
    cd= accept(sd,(struct sockaddr*)&cad,&cadl);
    printf("Enter your message: ");
    scanf("%s",str);
    send(cd,str,sizeof(str),0);
    close(cd);
    close(sd);
}