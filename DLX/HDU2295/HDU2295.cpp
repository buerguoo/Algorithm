#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
using namespace std;
const int maxnode = 3020;
const int MaxN = 55;
const int MaxM = 55;
int n, m, k;
const double eps = 1e-8;
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
            //printf(" c= %d\n",c);
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
struct point
{
    int x, y;
}city[MaxM], radar[MaxN];

double dis(point a, point b)
{
    return sqrt((double)(a.x-b.x)*(a.x-b.x) + (double)(a.y-b.y)*(a.y-b.y));
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        double l = 0, r = 1e8;
        scanf("%d%d%d", &n, &m, &k);
        for(int i = 0;i < n;++i)   scanf("%d%d", &city[i].x, &city[i].y);
        for(int i = 0;i < m;++i)   scanf("%d%d", &radar[i].x, &radar[i].y);
        while(r-l >= eps){
        double mid = (l + r) / 2.0;
        g.init(m, n);
        for(int i = 0;i < m;++i)
            for(int j = 0;j < n;++j)    
                if(dis(radar[i], city[j]) < mid-eps)
                    g.Link(i+1, j+1);
        if(g.Dance(0))
            r = mid - eps;
        else
            l = mid + eps;
        }
        printf("%.6lf\n", l);
    }
    return 0;
}