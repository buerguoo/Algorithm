/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:170ms
memory:3600kb

Data:May/08/2021 15:03
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
const int INF = 2e9+10;
const int MAXN = 1e5+10;
const int MAXM = 100010;
int main()
{
    int T, n;
    int x, p, a;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        x = INF;
        p = -1;
        for(int i = 0;i < n;++i){
            scanf("%d", &a);
            if(x > a) x = a, p = i;
        }    
        printf("%d\n", n-1);
        for(int i = 0;i < n;++i) if(i != p)
            printf("%d %d %d %d\n", p+1, i+1, x, x+abs(p-i));
    }
    return 0;
}