#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main()
{
    int sd, cd, dl, i, j, sl, cadl, c = 0, t = 0;
    struct sockaddr_in sad, cad;
    char data[100], data1[100];
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9994);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sd, (struct sockaddr *)&sad, sizeof(sad));
    listen(sd, 10);
    cadl = sizeof(cad);
    cd = accept(sd, (struct sockaddr *)&cad, &cadl);
    printf("Enter bitstream: ");
    scanf("%s", data);
    dl = strlen(data);
    while (1)
    {
        printf("Enter segment length: ");
        scanf("%d", &sl);
        if ((sl & (sl - 1)) == 0)
        {
            break;
        }
        else
        {
            printf("Enter segment again with respect to power of 2");
        }
    }

    if (dl % sl != 0)
    {
        i = sl - (dl % sl);
        for (j = 0; j < i; j++)
        {
            data1[j] = '0';
        }
        data1[j] = '\0';
        strcat(data1, data);
        strcpy(data, data1);
        dl = dl + i;
    }
    int sum[sl];
    for (int i = 0; i < sl; i++)
        sum[i] = 0;
    for (i = dl; i > 0; i = i - sl)
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

    printf("Sum is: ");
    for (j = 0; j < sl; j++)
    {
        if (sum[j] == 1)
            sum[j] = 0;
        else if (sum[j] == 0)
            sum[j] = 1;
        printf("%d ", sum[j]);
        data[dl + j] = sum[j] + 48;
    }
    data[dl + sl] = '\0';
    printf("code is: %s", data);
    send(cd, data, sizeof(data), 0);
    send(cd, &sl, sizeof(sl), 0);
    close(sd);
    close(cd);
}