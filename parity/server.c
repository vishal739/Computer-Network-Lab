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
    sad.sin_port= htons(9995);
    sad.sin_addr.s_addr= inet_addr("127.0.0.1");
    bind(sd,(struct sockaddr*)&sad,sizeof(sad));
    listen(sd, 10);
    cadl= sizeof(cad);
    cd= accept(sd,(struct sockaddr*)&cad,&cadl);

    printf("Enter bitstream: ");
    scanf("%s",str);
    int len=strlen(str);
    int cnt=0;
    for(int i=0;i<len;i++){
        if(str[i]=='1') cnt++;
    }
    int bit;
    printf("Enter \n1) Even Parity check \n2)Odd Parity check\n");
    scanf("%d",&bit);
    if(bit==1){
        if(cnt%2==0){
            str[len]='0';
        }else{
            str[len]='1';
        }
    }else{
        if(cnt%2==0){
            str[len]='1';
        }else{
            str[len]='0';
        }
    }
    str[len+1]='\0';
    send(cd,str,sizeof(str),0);
    send(cd,&bit,sizeof(bit),0);
    close(sd);
    close(cd);
}