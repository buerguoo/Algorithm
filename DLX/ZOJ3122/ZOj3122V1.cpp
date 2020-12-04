#include <fstream>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
const int maxnode = 16*16*4*16*17;
const int MaxN = 16*17*16;
const int MaxM = 16*16*4;
int X[MaxN], Y[MaxN], C[MaxN]; 
//答案对了 但是没有AC 懒得搞了
//精确覆盖
struct DLX
{
    int n,m,size;
    int U[maxnode],D[maxnode],R[maxnode],L[maxnode],Row[maxnode],Col[maxnode];
    int H[MaxN], S[MaxM];
    int ans[17][17];
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
    bool Dance(int d)
    {
        if(R[0] == 0)
            return true;
        int c = R[0];
        for(int i = R[0];i != 0;i = R[i])
            if(S[i] < S[c])
                c = i;
        remove(c);
        //printf("c = %d, D[c] = %d S[c] = %d\n", c, D[c], S[c]);
        for(int i = D[c];i != c;i = D[i])
        {
            //ans[d] = Row[i];
            //if(X[Row[i]] && Y[Row[i]])
            ans[X[Row[i]]][Y[Row[i]]] = C[Row[i]];
            //printf("Row[i] = %d, X[Row[i]] = %d, Y[Row[i] = %d, C[Row[i]] = %d\n"
            //, Row[i], X[Row[i]], Y[Row[i]], C[Row[i]]);
            for(int j = R[i]; j != i;j = R[j])remove(Col[j]);
            if(Dance(d+1))  return true;
            for(int j = L[i]; j != i;j = L[j])resume(Col[j]);
        }
        resume(c);
        return false;
    }
};

DLX g;
bool hashn[17][17], hashm[17][17], hashp[17][17], hash_[17][17];
char str[270];
int main()
{
        while(scanf("%s",&str) != EOF){
        g.init(MaxN, MaxM);
        memset(hashn, 0, sizeof(hashn));
        memset(hashm, 0, sizeof(hashm));
        memset(hashp, 0 , sizeof(hashp));
        memset(hash_, 0, sizeof(hash_));
        for(int i = 0;i < 16;++i)
            for(int j = 0;j < 16;++j){
                if(str[i*16+j] - 'A' >= 0 && str[i*16+j] - 'A' < 16)
                {
                    int t = str[i*16+j] - 'A' + 1;
                    hash_[i][j] = true;
                    hashn[i][t] = true;
                    hashm[j][t] = true; 
                    hashp[i/4*4+j/4][t] = true;
                    g.ans[i][j] = t;

                }
            }
        int row = 0;
        for(int i = 0;i < 16;++i)
            for(int j = 0;j < 16;++j){
                if(!hash_[i][j])
                {     
                    for(int k = 1;k <= 16;++k)
                        if(!hashn[i][k] && !hashm[j][k] && !hashp[i/4*4+j/4][k])
                        {
                            g.Link(++row, i*16+j+1);
                            g.Link(row,256+i*16+k);
                            g.Link(row, 512+j*16+k);
                            g.Link(row, 768+(i/4*4+j/4)*16+k);
                            X[row] = i, Y[row] = j, C[row] = k;

                        }
                }
                else
                {
                    int k = g.ans[i][j];
                    g.Link(++row, i*16+j+1);
                    g.Link(row,256+i*16+k);
                    g.Link(row, 512+j*16+k);
                    g.Link(row, 768+(i/4*4+j/4)*16+k);
                    X[row] = i, Y[row] = j, C[row] = k;
                }
                
            } 
        
        g.Dance(0);
        //printf("size = %d\n", g.size);
        for(int i = 0;i < 16;++i){
            for(int j = 0;j < 16;++j)
                printf("%c", g.ans[i][j] + 'A' - 1);
            printf("\n"); 
        }
    }
    //infile.close();
    //outfile.close();  
    return 0;
}