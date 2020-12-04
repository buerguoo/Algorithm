#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;
//并查集
const int MAXN = 650;
int F[MAXN];
int val[MAXN];
vector<int> Set[MAXN];
int DP[MAXN][MAXN];
int C[MAXN][2];
int num[MAXN];
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] = val[x] ^ val[F[x]];
    return F[x] = tmp;
}

int main()
{
    int n, p1, p2;
    while (~scanf("%d%d%d", &n, &p1, &p2))
    {
        if(n == 0 && p1 == 0 && p2 == 0)    break;
        int a, b, c;
        char s[5];
        memset(F, -1, sizeof(F));
        memset(val, 0, sizeof(val));
        memset(DP, 0, sizeof(DP));
        memset(C, 0, sizeof(C));
        memset(num, 0, sizeof(num));
        for(int i = 1;i <= p1+p2;++i)   Set[i].clear();
        for(int i = 0;i < n;++i){
           scanf("%d%d%s", &a, &b, s);
            if(s[0] == 'y')   c = 0;
            else    c = 1;
            int t1 = find(a);
            int t2 = find(b);
            if(t1 != t2){
                F[t2] = t1;
                val[t2] = val[a] ^ val[b] ^ c;
            }    
        }
        int tol = 0;
        for(int i = 1;i <= p1+p2;++i){
            if(i != find(i))    continue;
            tol++;
            for(int j = 1;j <= p1+p2;++j){
                if(i != find(j))    continue;
                Set[tol].push_back(j);
                if(val[j] == 0) C[tol][0]++;
                else C[tol][1]++;
            }
        }
        DP[0][0] = 1;
        for(int i = 1;i <= tol;++i){
            for(int j=p1;j>=C[i][0];--j)
                DP[i][j] += DP[i-1][j-C[i][0]];     
            for(int j=p1;j>=C[i][1];--j) 
                DP[i][j] += DP[i-1][j-C[i][1]];
        }
        int co = 0;
        if(DP[tol][p1] != 1)    printf("no\n");
        else{
            for(int i = tol;i > 0;--i){
                if(DP[i-1][p1-C[i][0]] == 1){
                    for(int j = 0;j < Set[i].size();++j)
                        if(val[Set[i][j]] == 0)
                            num[co++] = Set[i][j];
                    p1 -= C[i][0]; 
                }
                else{
                     for(int j = 0;j < Set[i].size();++j)
                        if(val[Set[i][j]] == 1)
                            num[co++] = Set[i][j];
                    
                    p1 -= C[i][1];
                }
            }
            sort(num, num+co);
            for(int i = 0;i < co;++i)
                printf("%d\n", num[i]);
            printf("end\n");
        } 
    }
    return 0;
}