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
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] ^= val[F[x]];
    return F[x] = tmp;
}

int main()
{
    ifstream infile;
    infile.open("D://input.txt", ios::in);
    int n, x;
    //~scanf("%d",&x)
    while (infile >> x)
    {
        int u, v, c;
        char s[5] = "";
        infile >> n;
        //scanf("%d", &n);
        for(int i = 0;i <= 2*n;++i){
            F[i] = -1;
            val[i] = 0;
        }
        M[0] = 0;
        for(int i = 1;i <= n;++i){
            //scanf("%d%d%s", &u, &v, s);
            infile >> u >> v >> s;
            M[u] = i;
            M[v] = 2*i-1;
            if(s[0] == 'o')     c = 1;
            else c = 0;
            int t1 = find(M[u]);
            int t2 = find(M[v]);
            if(t1 != t2){
                F[t2] = t1;
                if(t1)  F[M[u]] = M[u-1];
                val[t2] = val[u] ^ val[v] ^ c;
            }
            else
            {
                if(val[u] ^ val[v] != c)
                    {
                        printf("%d\n", i);
                        break;
                    }
            }
            
        }
        //for(int i = 1;i <= x;++i)
               // printf("F[%d] = %d\n",i, F[i]);
    }
    infile.close();
    return 0;
}