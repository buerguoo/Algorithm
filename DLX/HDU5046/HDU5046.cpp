#include <cstring>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <cmath>
#define LL __int64
using namespace std;
const int maxnode = 65*60;
const int MaxN = 65;
const int MaxM = 65;
const int INF = 1.4e9;
const double eps = 0.1;
int k;
//重复覆盖
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN], S[MaxM];
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
    bool Dance(int d)
    {
        //printf("d = %d\n", d);
        if(d + f() > k) return false;
        if(R[0] == 0)
            return d <= k;
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        for(int i = D[c];i != c;i = D[i])
        {
            remove(i);
            for(int j = R[i]; j != i;j = R[j])  remove(j);
            if(Dance(d+1))  return true;
            for(int j = L[i]; j != i;j = L[j])  resume(j);
            resume(i);
        }
        return false;
    }
};

DLX g;

struct point{
    int x,y;
}P[MaxM];

double dis(point a, point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x)+(double)(a.y-b.y)*(a.y-b.y));
}

int main()
{
    int T, t;
    scanf("%d", &T);
    t = T;
    while(T--)
    {
        int n;
        scanf("%d%d", &n,&k);
        for(int i = 0;i < n;++i)
            scanf("%d%d", &P[i].x, &P[i].y);
        int l = 0, mid;
        int r = INF;
        while(r >= l)
        {
            g.init(n, n);
            mid = (r+l) / 2;
           // printf("mid = %lf r = %lf l = %lf\n", mid, r, l);
            for(int i = 0;i < n;++i)
                for(int j = 0;j < n;++j)
                    if(dis(P[i], P[j]) < mid)
                        g.Link(i+1, j+1);

            if(g.Dance(0))  r = mid+1;
            else l = mid-1;
        }
        
        printf("Case #%d: %d\n", t-T, r);
    }
    return 0;
}