/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:15ms
memory:1760kB

Data:2021-04-14 22:55:43
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
const int MAXN = 1010;
const int MAXM = 100010;
int dp[MAXN], pre[MAXN];
struct mouse{
    int w, p, ind;
    bool operator<(const mouse &a) const{
        if(w == a.w) return p > a.p;
        return w < a.w;
    }
}mice[MAXN];
void output(int x)
{
    if(!x) return ;
    output(pre[x]);
    printf("%d\n", mice[x].ind);
}
int main()
{
    int n = 1;
    while(scanf("%d %d", &mice[n].w, &mice[n].p) != EOF){
        mice[n].ind = n;
        n++;
        //n++;
        }
        sort(mice+1, mice+n);
        mice[0].p = INF, mice[0].w = 0;
        dp[0] = 0;
        memset(pre, 0, sizeof(pre));
        for(int i = 1;i < n;++i){
            dp[i] = 0;
            for(int j = 0;j < i;++j)
                if(mice[i].w > mice[j].w && mice[i].p < mice[j].p && dp[i] < dp[j]+1){
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
        }
        int k = -1, Max = 0;
        for(int i = 1;i < n;++i)        
            if(Max < dp[i]){
                Max = dp[i];
                k = i;
            }
        printf("%d\n", Max);
        output(k);
        
    return 0;
}