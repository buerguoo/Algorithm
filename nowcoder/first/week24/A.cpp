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
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int MAXN = 20;
int tp1[MAXN] = {0}, tp2[MAXN] = {0};
int tran(int x, int tp[])
{
    int co = 0;
    while(x){
        tp[co++] = x & 1;
        x = x >> 1;
    }
    return co;
}
int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    int len = max(tran(a, tp1), tran(b, tp2));
    for(int i = len-1;i >= 0;--i) printf("%d", tp1[i]+tp2[i]);
    printf("\n");
    return 0;
}