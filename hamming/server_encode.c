#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void printCodeword(char *codeword) {
  printf("Codeword is: ");
  int len = strlen(codeword);
  for (int i = 1; i <= len; i++) {
    printf("%c", codeword[i]);
  }
  printf("\n");
}

int main() {
  int sd, cd, cadl;
  char str[64];
  char codeword1[64];
  struct sockaddr_in sad, cad;
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  sad.sin_port = htons(9995);
  bind(sd, (struct sockaddr*)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr*)&cad, &cadl);
  recv(cd, codeword1, sizeof(str), 0);
  recv(cd, str, sizeof(str), 0);
  printCodeword(codeword1);

  int data_len = strlen(str);
  int redundant_bits = 0;

  while (true) {
    if (pow(2, redundant_bits) >= data_len + redundant_bits + 1)
      break;
    redundant_bits++;
  }
  char codeword[64] = {'0'};
  int total_len = data_len + redundant_bits;
  for (int i = 0; i < redundant_bits; i++) {
    codeword[total_len + 1 - (int)pow(2, i)] = 'P';
  }

  int curridx = 0;
  for (int i = 1; i <= total_len; i++) {
    if (codeword[i] != 'P') t
      codeword[i] = str[curridx++];
  }
  codeword[total_len + 1] = '\0'; 
  for (int i = total_len; i >= 1; i--) {
    if (codeword[i] == 'P') {
      int limit = total_len - i + 1;
      int index = i;
      bool ignore = false;
      int countOne = 0;
      while (index > 0) {      
        int codelimit = limit; 
        if (!ignore) {
          while (codelimit > 0 && index > 0) { 
            if (codeword[index] != 'P' && codeword[index] == '1') {
              countOne++;
            }
            index--;
            codelimit--;
          }
        } else {
          while (codelimit > 0 && index > 0) { 
            index--;
            codelimit--;
          }
        }
        ignore = !ignore; 
      }
      codeword[i] = countOne % 2 ? '1' : '0';
      countOne = 0; 
    }
  }
  printf("Server generated ");
  printCodeword(codeword);
  printf("Checking...\n");
  for(int i = 0; i < strlen(codeword1); i++) {
    if(codeword1[i] != codeword[i]) {
        printf("There is error in data\n");
        return 1;
    }
  }
  printf("Data received in OK condition\n");
  close(cd);
  close(sd);
}