#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
#include <fstream>
using namespace std;
//辛辛苦苦这么长时间 结果TLE  WDNMDDDDDDD      
const int a[5] = {1, 5, 14, 30, 55};
const int N = 5;
const int MaxN = 2*N*(N+1);
const int MaxM = 55;
const int maxnode = MaxN*MaxM;
const int INF = 0x3f3f3f3f;
int K, tp[MaxN];
int n;
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd;
    void init(int _n,int _m)
    {
        n = _n;
        m = _m;
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
        //printf("r = %d, c = %d\n",r ,c);
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
        //printf("c = %d\n", c);
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
        for(int c = R[0];c != 0;c = R[c])
        if(v[c])
        {
            rel++;
            //printf("%d %d\n",c,v[c]);
            v[c] = false;
            for(int i = D[c];i != c;i = D[i])
                for(int j = R[i];j != i;j = R[j])
                    v[Col[j]] = false;
        }
       // printf("rel  = %d\n", rel);
        return rel;
    }
    //d为递归深度
    void Dance(int d)
    {
        //printf("d = %d\n", d);
        if(d + f() >= ansd) return ;
        if(R[0] == 0)
        {
            if(d < ansd)   ansd = d;
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
    }
};
DLX g;
struct stick
{
    int num;
    bool index;
}ss[2*N*(N+1)][N+1];
//打表
void square(int x, int y, int x1, int y1, int p)
{
    for(int i = x;i <= x1;++i)
    {
        if(i % 2 == 0){
        g.Link(ss[i-1][y-1].num, p);
        if(!ss[i-1][y-1].index && K > 0)
            tp[--K] = g.size;
        }
    }   
    for(int i = y;i <= y1;++i){
        g.Link(ss[x-1][i-1].num, p);
        if(!ss[x-1][i-1].index && K > 0)
            tp[--K] = g.size;

    }  
    for(int i = x+1;i <= x1;++i){
        if(i % 2 == 0){
        g.Link(ss[i-1][y1].num, p);
        if(!ss[i-1][y1].index && K > 0)
            tp[--K] = g.size;
        }
    }   
    for(int i = y;i <= y1;++i){
        g.Link(ss[x1-1][i-1].num, p);
        if(!ss[x1-1][i-1].index && K > 0)
            tp[--K] = g.size;
    }    
        
}
void Init()
{
    int p = 0, t = 0;
    for(int i = 0;i < 2*n+1 ;++i)
        for(int j = 0;j < n+(i%2);++j)
        {
            ss[i][j].num = (++p);
            ss[i][j].index = true;
            
            if(t < K && tp[t] == p)
            {
                t++;
                ss[i][j].index = false;
            }
        }        
    p = 0,t = K;
    for(int i = 0;i < 2*n+1 ;i += 2)
        for(int j = 0;j < n;++j)
        {
            //上下两个正方形共用一个上边和下边
            for(int x = 1;x <= n;x++) if(j + x <= n && i+2*x < 2*n+1)
                square(i+1, j+1, i+2*x+1, j+x, ++p);
        }

       for(int i = 0;i < t;i++)
           for(int c = g.R[tp[i]];c != tp[i];c = g.R[c])
                g.remove(c);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &K);
        for(int i = 0;i < K;++i)
            scanf("%d", &tp[i]);
        g.init(2*n*(n+1), a[n-1]);
        Init();
        g.ansd = INF;
        g.Dance(0);
        printf("%d\n", g.ansd);

    }
    return 0;
}