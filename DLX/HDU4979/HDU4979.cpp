#include <cstring>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <cmath>
#define LL __int64
using namespace std;
const int maxnode = 100*100;
const int MaxN = 100;
const int MaxM = 100;
const int INF = 1e9;
//重复覆盖
struct DLX
{
    int n,m,size, k = INF;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN], S[MaxM];
    void init(int _n,int _m)
    {
        n = _n;
        m = _m;
        k = INF;
        for(int i = 0;i <= m;i++)
        {
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;
        for(int i = 1;i <= n;i++)
            H[i] = -1;
    }
    void Link(int r,int c)
    {
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else
        {
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
    //此为重复覆盖， 不需要删除冲突行
    void remove(int c)
    {
        for(int i = D[c];i != c;i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            L[R[i]] = R[L[i]] = i;
    }

    //预测剪枝
    bool v[maxnode];
    int f()
    {
        int rel = 0;
        for(int c = R[0];c != 0;c = R[c])
            v[c] = true;
        for(int c = R[0];c != 0;c = R[c]){   
        if(v[c])
            {
            rel++;
            v[c] = false;
            for(int i = D[c];i != c;i = D[i])
                for(int j = R[i];j != i;j = R[j])
                    v[Col[j]] = false;
            }
        }
        //printf("rel  = %d\n", rel);
        return rel;
    }

    //d为递归深度
    void Dance(int d)
    {
        //printf("d = %d\n", d);
        if(d + f() > k) return;
        if(R[0] == 0)
        {
            if(d < k)
                k = d;
            return ;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i])
        {
            remove(i);
            for(int j = R[i]; j != i;j = R[j])  remove(j);
            Dance(d+1);
            for(int j = L[i]; j != i;j = L[j])  resume(j);
            resume(i);
        }
        return;
    }
};

DLX g;
int c[10][10];
int bitcount[1024];
int vis[1024];

int Get(int x)
{
    int ans = 0;
    while(x)
    {
        ans += (x&1);
        x = x >> 1;
    }
    return ans;
}

void Init()
{
    memset(c, 0, sizeof(c));
    for(int i = 0;i <= 8;++i)
        c[i][0] = 1;
    for(int i = 1;i <= 8;++i)
        for(int j = 1;j <= i;++j)
            c[i][j] = c[i-1][j-1] + c[i-1][j];

    for(int i = 1;i <= (1<<8);++i)
        bitcount[i] = Get(i); 
}

int main()
{


    //int T, t;
    ///scanf("%d", &T);
    Init();
    //t = T;
    //while(T--)
    //{
        int n, m, r;
        for(n = 1;n <= 8;n++){printf("{\n");
            for(m = 1;m <= n;m++){
                printf("{");
                for(r = 1;r <= m;r++)
        {
        memset(vis, 0, sizeof(vis));
        g.init(c[n][m], c[n][r]);
        for(int i = 1,k = 0;i < (1<<n);++i)
            if(bitcount[i] == r)
                vis[i] = ++k;
        
        for(int i = 1,k = 0;i < (1<<n);++i)
        {
            if(bitcount[i] == m)
            {
                ++k;
                for(int j = i;j;j = (j-1)&i)
                    if(bitcount[j] == r)
                        g.Link(k, vis[j]);
            }
        }
    g.Dance(0);
    printf("%d ",g.k);
    //printf("Case #%d: %d\n",t-T, g.k);
    }
    printf("},\n");
            }
            printf("},\n");
                }
    return 0;
}
