#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main()
{
    int c = 0, t = 0, sd, i, j, sl, dl;
    char data[100];
    struct sockaddr_in sad;
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9994);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sd, (struct sockaddr *)&sad, sizeof(sad));
    recv(sd, data, sizeof(data), 0);
    recv(sd, &sl, sizeof(sl), 0);
    dl = strlen(data);
    printf("Recieved in client %s\n", data);

    printf("sl: %d", sl);
    int sum[sl];
    printf("data copied\n");
    for (int i = 0; i < sl; i++)
        sum[i] = 0;
    for (i = dl; i > 0; i -= sl)
    {
        int k = sl - 1;
        c = 0;
        for (j = i - 1; j >= i - sl; j--)
        {
            t = sum[k] + (data[j] - 48) + c;
            sum[k] = t % 2;
            c = t / 2;
            k--;
        }
        if (c == 1)
        {
            for (j = sl - 1; j >= 0; j--)
            {
                t = sum[j] + c;
                sum[j] = t % 2;
                c = t / 2;
            }
        }
    }
    printf("sum is: ");
    for (int i = 0; i < sl; i++)
    {
        printf("%d ", sum[i]);
    }
    printf("\n");
    j = 0;
    for (i = 0; i < sl; i++)
    {
        if (sum[i] != 1)
        {
            j++;
            break;
        }
    }
    if (j == 0)
    {
        printf("\n data recv ok \n");
        printf("\n ACTUAL data IS: \n");
        for (i = 0; i < dl - sl; i++)
            printf("%c ", data[i]);
    }
    else
    {
        printf("Error in codeword is recieved %s\n", data);
    }
    close(sd);
}