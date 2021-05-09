/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:202 ms
memory:11396 KB

Data:2021-05-09 11:57:36
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
typedef long long ll;
typedef vector<int> vi;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
const int MAXM = 100010;
struct node{
    int xl, yl, xr, yr;
};
vi g[MAXN];
vector<node> ans;
//y数组用来记录这个结点最左的最深叶子节点
//最巧妙的是z数组，用来记录第二左的最深叶子节点
//但由于情况1我们最终全部会剪枝为子节点为2的，所以z数组便是最右最深结点
//并且利用z数组，我们可以判断结点的子孩子的数量
int y[MAXN], z[MAXN], n;
void dfs(int u, int fa)
{
    y[u] = u, z[u] = 0;
    vi q;
    for(auto &v:g[u]){
        if(v == fa) continue;
        dfs(v, u);
        if(z[v]) q.push_back(v);
        else{
            if(y[u] == u) y[u] = y[v];
            else if(!z[u]) z[u] = y[v];
            else{
                ans.push_back({u, v, v, y[u]});
                y[u] = y[v];
            }
        }
    }
    for(auto &v:q){
        ans.push_back({u, v, y[v], y[u]});
        y[u] = z[v];
    }
}
int main()
{
    int T;
    int u, v;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1;i <= n;i++) g[i].clear();
        ans.clear();
        for(int i = 0;i < n-1;++i){
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        printf("%d\n", ans.size());
        for(auto &it:ans)
            printf("%d %d %d %d\n", it.xl, it.yl, it.xr, it.yr);

    }
    return 0;
}
