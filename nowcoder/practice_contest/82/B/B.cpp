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
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 100010;
//...
ll sum[MAXN<<2];
int a[MAXN];
void pushup(int rt){sum[rt] = sum[rt<<1]*sum[rt<<1|1];}
void build(int l, int r, int rt)
{
    if(l == r){
        sum[rt] = a[l];
        return ;
    }
    int m = (l + r) >> 1;
    build(l, m, rt<<1);
    build(m+1, r, rt<<1|1);
    pushup(rt);
}
void update(int L, int R, int l, int r, int rt, int k)
{
    if(l == r){
        if(!k) sum[rt] = (sum[rt] * sum[rt]) % (l - L + 1);
        else sum[rt] = (k * sum[rt]) % (l - L + 1);
    }
    int m = (l + r) >> 1;
    if(l <= R) update(L, R, l, m, rt<<1, k);
    if(r >= L) update(L, R, m+1, r, rt<<1|1, k);
    pushup(rt);
}
ll query(int L, int R, int l, int r, int rt){
    if(L <= l && R >= r){
        return sum[rt];
    }
    ll ans = 1;
    int m = (l + r) >> 1;
    if(l <= R) ans * query(L, R, l, m, rt<<1);
    if(r >= L) ans * query(L, R, m+1, r, rt<<1|1);
    return ans;
}
int main()
{
    int n, m;
    int l, r, k;
    scanf("%d %d", &n, &m);
    build(1, n, 1);
    while(m--){

    }
    return 0;
}