#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//并查集
const int MAXN = 30010;
int pre[MAXN], a[MAXN];

int find(int s)
{
    int root = s, tmp;
    while(pre[root] != root)    root = pre[root];
    while(pre[s] != root){
        tmp = pre[s];
        pre[tmp] = root;
        s = tmp;
    }

    return root;
}

void merge(int x, int y)
{
    if((x=find(x)) == (y=find(y)))  return;

    pre[y] = x;
    a[x] += a[y]; 
}

int main()
{
    int m, n;
    while(~scanf("%d%d", &n, &m)){
        if(n == 0 && m == 0)    break;
        for(int i = 0;i < n;++i){
            pre[i] = i;
            a[i] = 1;
        }
        for(int i = 0;i < m;++i){
            int k;
            int x, y;
            scanf("%d%d", &k, &x);
            for(int j = 1;j < k;++j){
                scanf("%d", &y);
                merge(x, y);
            }
        }
        printf("%d\n", a[find(0)]);
    }
    return 0;
}
