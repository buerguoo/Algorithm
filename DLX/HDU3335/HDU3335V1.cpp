#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <cmath>
#define LL __int64
using namespace std;
const int maxnode = 1010*1010;
const int MaxN = 1010;
const int MaxM = 1010;
int k = 0, n;
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
    void Dance(int d)
    {
        //printf("d = %d\n", d);
        if(d + f() <= k) return ;
        if(R[0] == 0)
        {
            if(d > k)
                k = d;
            return;
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
LL num[MaxN+1];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d", &n);
        memset(num, 0, sizeof(num));
        for(int i = 1;i <= n;++i)
            scanf("%lld", &num[i]);
        g.init(n, n);
        
        for(int i = 1;i <= n;++i)
            for(int j = 1;j <= n;++j)
                if(num[i]%num[j]==0 || num[j]%num[i]==0)
                    g.Link(i, j);
        k = 0;
        g.Dance(0);

        printf("%d\n", k);

    }
    return 0;
}