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
const int MAXN = 10001;
int F[MAXN], val[MAXN];
int judge[MAXN];
struct Cmp
{
    int a, b, d;
}C[MAXN];
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] = (val[x]+val[F[x]]) % 3;
    return F[x] = tmp;
}
void Init(int n)
{
    for(int i = 0;i < n;++i){
        F[i] = -1;
        val[i] = 0;
    }
}
int main()
{
    int N, M;
    while (~scanf("%d%d", &N, &M))
    {
        char c;
        for(int i = 0;i < M;++i)
        {
            scanf("%d%c%d", &C[i].a, &c, &C[i].b);
            if(c == '=')    C[i].d = 0;
            else if(c == '>')   C[i].d = 1;
            else if(c == '<')   C[i].d = 2;
        }
        memset(judge , -1, sizeof(judge));
        for(int i = 0;i < N;++i){
            Init(N);
            for(int j = 0;j < M;++j){
                int a = C[j].a, b = C[j].b;
                if(a == i || b == i)    continue;
                int t1 = find(a);
                int t2 = find(b);
                if(t1 != t2){
                    F[t2] = t1;
                    val[t2] = (val[a]+C[j].d-val[b]+3) % 3;
                }
                else{
                    if(C[j].d != (val[b]-val[a]+3) % 3){
                        judge[i] = j+1;
                        break;
                    }
                }
            }
        }
        int ans1 = 0, ans2 = 0, cnt = 0;
        for(int i = 0;i < N;++i)
        {
            if(judge[i] == -1){
                cnt++;
                ans1 = i;
            }
            ans2 = max(ans2, judge[i]);
        }
        if(cnt == 0)    printf("Impossible\n");
        else if(cnt == 1)   
            printf("Player %d can be determined to be the judge after %d lines\n", ans1, ans2);
        else    printf("Can not determine\n");   
    }
    
    return 0;
}