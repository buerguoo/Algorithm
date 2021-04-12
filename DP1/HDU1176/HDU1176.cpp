/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:46ms
memory:6044kB

Data:2021-04-12 22:51:12
*/
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
const int MAXM = 100010;
int T[MAXN][11];
int main()
{
    int n;
    int x, t;
    while(~scanf("%d", &n) && n){
        int Max = 0;
        memset(T, 0, sizeof(T));
        while(n--){
            scanf("%d %d", &x, &t);
            T[t][x]++;
            Max = max(Max, t);
        }
        for(int i = Max-1;i >= 0;--i){
            for(int j = 1;j < 10;++j)
                T[i][j] += max(max(T[i+1][j-1], T[i+1][j]), T[i+1][j+1]);
            T[i][0] += max(T[i+1][0], T[i+1][1]);
            T[i][10] += max(T[i+1][9], T[i+1][10]);
        }
        printf("%d\n", T[0][5]);
    }
    return 0;
}
