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
const int MAXN = 500010;
const int MAXM = 100010;
int a[MAXN];
bool cmp(int x, int y)
{
    return x > y;
}
int main()
{
    int n, h, u;
    scanf("%d %d %d", &n, &h, &u);
    for(int i = 0;i < n;++i) scanf("%d", &a[i]);
    sort(a, a+n, cmp);
    int ans = 0;
    for(int i = 0;i < n;++i){
        if(h >= u) break;
        h += a[i];
        ans++;
    }
    printf("%d\n", ans);
    return 0;
}