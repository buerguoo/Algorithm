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
const int MAXN = 1e4+10;
int F[MAXN];
int val[MAXN];
map <int, int> M;
int find(int x)
{
    //printf("%d\n", x);
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] ^= val[F[x]];
    return F[x] = tmp;
}

int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
        int n, x;
        scanf("%d%d",&x, &n);
        int u, v, c;
        char s[5] = "";
        //infile >> n;
        M.clear();
        memset(F, -1, sizeof(F));
        memset(val, 0, sizeof(val));
        int co = 1, ans = 0;
        for(int i = 0;i < n;++i){
            scanf("%d%d%s", &u, &v, s);
            //infile >> u >> v >> s;
            u--;
            if(!M[u])    M[u] = co++;
            if(!M[v])    M[v] = co++;
            if(s[0] == 'o')     c = 1;
            else c = 0;
            int t1 = find(M[u]);
            int t2 = find(M[v]);
            if(t1 != t2){
                F[t2] = t1;
                val[t2] = val[M[u]] ^ val[M[v]] ^ c;
            }
            else
                if(val[M[u]] ^ val[M[v]] != c && ans==0)
                    ans = i;
            
        }
        //for(int i = 1;i <= x;++i)
               // printf("F[%d] = %d\n",i, F[i]);
    //infile.close();
    if(!ans)    ans = n;
    printf("%d\n", ans);
    return 0;
}