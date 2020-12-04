#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//Foyld闭包传递
const int MAXN = 110;
const int INF = 0x3f3f3f3f;
bool e[MAXN][MAXN];

int Folyd(int n)
{
    for(int k = 1;k <= n;++k)
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(e[i][k] && e[k][j])
                    e[i][j] = true;
    
    int ans = 0;
    for(int i = 1;i <= n;++i)
    {
        int tmp = 0;
        for(int j = 1;j <= n;++j)
            if(e[i][j] || e[j][i])
                tmp++;
        if(tmp == n-1)
            ans++;
    }

    return ans;
}

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    int x, y;
    memset(e, false, sizeof(e));
    for(int i = 0;i < M;++i){
        scanf("%d%d", &x, &y);
        e[x][y] = true;
        }
    printf("%d\n", Folyd(N));
    return 0;
}