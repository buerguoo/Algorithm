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
const int MAXN = 10010;
const int MAXM = 100010;
int main()
{
    ll k, a, b;
    int ans = -1;
    scanf("%lld %lld %lld", &k, &a, &b);
    if(k > 0 && k <= a) ans = 1;
    else if(k*(a-b) <= 0) ans = -1;
    else{
        if(k > 0) ans = (k-a)/(a-b)+ 1 + ((k-a)%(a-b)==0?0:1);
        else ans = k/(a-b) + (k%(a-b)==0?0:1);
    }
    printf("%d\n", ans);
    return 0;
}