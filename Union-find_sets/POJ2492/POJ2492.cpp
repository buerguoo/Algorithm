#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;
//并查集
const int MAXN = 2010;
int F[MAXN], val[MAXN];
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] = (val[x]+val[F[x]])%2;
    return F[x] = tmp;
}
int main()
{
    int T, t = 0;
    scanf("%d", &T);
    while (t++ < T)
    {
        int N, M;
        bool door = false;
        scanf("%d%d", &N, &M);
        memset(F, -1, sizeof(F));
        memset(val, 0, sizeof(val));
        for(int i = 0;i < M;++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            int t1 = find(a);
            int t2 = find(b);
            if(t1 != t2){
                F[t2] = t1;
                val[t2] = (val[a]+val[b]+1)%2;
            }
            else{
                if(val[a] == val[b])
                    door = true;   
        }
    }
    printf("Scenario #%d:\n", t);
    if(door)    printf("Suspicious bugs found!\n\n");
    else printf("No suspicious bugs found!\n\n");
    }
    return 0;
}