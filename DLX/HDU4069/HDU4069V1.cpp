#include <fstream>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
const int maxnode = 9*9*4*9*10;
const int MaxN = 9*10*9;
const int MaxM = 9*9*4;
const int n = 15;
int X[MaxN], Y[MaxN], C[MaxN];
int P[n][n], a[n][n];
bool f[n][n][4]; 
//使用文件读取输出时正确，但是却不过，不知道他妈的为什么
//精确覆盖
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN], S[MaxM];
    int ansd, ans[10][10];
    bool flag;
    void init(int _n,int _m)
    {
        n = _n;
        m = _m;
        flag = false;
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
    void remove(int c)
    {
        L[R[c]] = L[c]; R[L[c]] = R[c];
        for(int i = D[c];i != c;i = D[i])
            for(int j = R[i];j != i;j = R[j])
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[Col[j]];
            }
    }
    void resume(int c)
    {
        for(int i = U[c];i != c;i = U[i])
            for(int j = L[i];j != i;j = L[j])
                ++S[Col[U[D[j]]=D[U[j]]=j]];
        L[R[c]] = R[L[c]] = c;
    }
    //d为递归深度
    int Dance(int d)
    {
        if(R[0] == 0)
        {
            if(!flag)   {flag = true; return 0;}
            return 1;
        }
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        remove(c);
        for(int i = D[c];i != c;i = D[i])
        {
            //ans[d] = Row[i];
            ans[X[Row[i]]][Y[Row[i]]] = C[Row[i]];
           // printf("Row[i] = %d, X[Row[i]] = %d, Y[Row[i] = %d, C[Row[i]] = %d\n"
            //, Row[i], X[Row[i]], Y[Row[i]], C[Row[i]]);
            for(int j = R[i]; j != i;j = R[j])remove(Col[j]);
            if(Dance(d+1))  return 2;
            for(int j = L[i]; j != i;j = L[j])resume(Col[j]);
        }
        resume(c);
        if(d == 0 && flag)  return 1;
        return 0;
    }
    void display()
    {
        for(int i = 0;i < 9;++i)
            for(int j = 0;j < 9;++j)
                printf("%d%s", ans[i][j],j == 8 ? "\n":"");
    }
};

int find(int x, int y, int &z)
{
    if(z >= 128)    z -= 128, f[x][y][0] = 1;
    if(z >= 64)     z -= 64, f[x][y][1] = 1;
    if(z >= 32)     z -= 32, f[x][y][2] = 1;
    if(z >= 16)     z -= 16, f[x][y][3] = 1;
    return 0;
}

int get(int x, int y, int flag)
{
    if(P[x][y]) return 0;
    P[x][y] = flag;
    if(!f[x][y][0]) get(x, y-1, flag);
    if(!f[x][y][1]) get(x+1, y, flag);
    if(!f[x][y][2]) get(x, y+1, flag);
    if(!f[x][y][3]) get(x-1, y, flag);

    return 0;
}
inline void read(int &ret)
{
	char c;
	do {
		c = getchar();
	} while (c < '0' || c > '9');
	ret = c - '0';
	while ((c = getchar()) >= '0' && c <= '9')
		ret = ret * 10 + (c - '0');
}
DLX g;
bool hashn[n][n], hashm[n][n], hashp[n][n];
int main()
{
    int T, t = 0;
    scanf("%d", &T);
    while(T--)
    {
        g.init(MaxN, MaxM);
        memset(f, 0, sizeof(f));
        memset(hashn, 0, sizeof(hashn));
        memset(hashm, 0, sizeof(hashm));
        memset(hashp, 0 , sizeof(hashp));
        memset(P, 0, sizeof(P));
        for(int i = 0;i < 9;++i)
            for(int j = 0;j < 9;++j)
                read(a[i][j]), find(i, j, a[i][j]);
        int p = 0;
        for(int i = 0;i < 9;++i)
            for(int j = 0;j < 9;++j)
                if(!P[i][j])    get(i, j, ++p);
        for(int i = 0;i < 9;++i)
            for(int j = 0;j < 9;++j)
            {
                if(a[i][j])
                {
                    int k = a[i][j];
                    hashn[i][k] = 1;
                    hashm[j][k] = 1;
                    hashp[P[i][j]][k] = 1;
                    g.ans[i][j] = k;
                }
            }   
        int row = 0;
        for(int i = 0;i < 9;++i)
            for(int j = 0;j < 9;++j){
                if(!a[i][j])
                {
                    for(int k = 1;k <= 9;++k)
                        if(!hashn[i][k] && !hashm[j][k] && !hashp[P[i][j]][k])
                        {
                            g.Link(++row, i*9+j+1);
                            g.Link(row, 81+i*9+k);
                            g.Link(row, 162+j*9+k);
                            g.Link(row, 243+(P[i][j]-1)*9+k);
                            X[row] = i, Y[row] = j, C[row] = k;

                        }
                }
                else
                {
                    int k = g.ans[i][j];
                    g.Link(++row, i*9+j+1);
                    g.Link(row, 81+i*9+k);
                    g.Link(row, 162+j*9+k);
                    g.Link(row, 243+(P[i][j]-1)*9+k);
                    X[row] = i, Y[row] = j, C[row] = k;
                }
                
            } 
        printf("Case %d:\n", ++t);
        switch(g.Dance(0))
        {
            case 0:printf("No solution\n"); break;
            case 1:g.display(); break;
            case 2:printf("Multiple Solutions\n");  break;
        }
            
    }
    return 0;
} 