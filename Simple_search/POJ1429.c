#include <stdio.h>
#include <string.h>
#define MAXN 1000000

int mod[MAXN];
int ans[100];
int n;

int main()
{
    int m,i;
    while(scanf("%d",&n) && n != 0){
        memset(mod,0,sizeof(mod));
        mod[1] = 1;
        m = 0;
        for(i = 2;mod[i-1] != 0;i++)
            mod[i] = (mod[i/2] * 10 + i % 2) % n;
        i--;
        do{
            ans[m++] =  i % 2;
            i /= 2;

        }while(i >= 1);
        for(int j = m - 1;j >= 0;j--)
            printf("%d",ans[j]);
        printf("\n");
    }

    return 0;
}
