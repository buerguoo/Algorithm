#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//并查集
const int MAXN = 1010;
int pre[MAXN];
int N;

void Init(int n)
{
    for(int i = 0;i <= n;++i)    pre[i] = i;
}

int find(int s)
{
    int root = s, tmp;
    while(pre[root] != root)    root = pre[root];
    while (pre[s] != root)
    {
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
    N--;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        N = n;
        Init(n);
        int a, b;
        for(int i = 0;i < m;++i){
            scanf("%d%d", &a, &b);
            merge(a, b);
        }
        printf("%d\n", N);
    }
    
    return 0;
}