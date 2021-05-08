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
    ll d = 0;
    ll ans = 1;
    scanf("%lld %lld %lld", &k, &a, &b);
    if(k < 0){
        k = -k;
        swap(a, b);
    }
    if(a <= b){
        ans = -1;
    }else{
        while((d + a) < k){
            ans++;
            d += a - b;
        }
    }
    printf("%lld\n", ans);
    return 0;
}