#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
const int MAXN = 10000;
const int MAXM = 500;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ls(i) i<<1
#define rs(i) i<<1|1

int Pro[MAXM], Start[MAXM];
int pre[MAXN<<2], suf[MAXN<<2], Max[MAXN<<2];
bool vis[MAXN];
map<int, int> M;

void PushUp(int rt, int len)
{
    pre[rt] = 
}