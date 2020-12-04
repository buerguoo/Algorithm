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
//找不到哪里错就离谱
const int MAXN = 40100;
int F[MAXN];
int X[MAXN], Y[MAXN];
int ans[10005];
struct Farm
{
    int a, b, x, y;
    Farm(int _a=0,int _b=0, int _x=0, int _y=0):a(_a), b(_b), x(_x), y(_y)
    {}
}Fa[MAXN];
struct Query{
    int a, b, pos, index;
    Query(int _a=0, int _b=0, int _p=0, int _i=0):a(_a), b(_b), pos(_p), index(_i){}
}Q[10005];
bool cmp(const Query &q1,const Query &q2)
{
    return q1.pos < q2.pos;
}
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    X[x] += X[F[x]];
    Y[x] += Y[F[x]];
    return F[x] = tmp;
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int N, M;
    scanf("%d%d", &N, &M);
    //infile >> N >> M;
    memset(F, -1, sizeof(F));
    memset(X, 0, sizeof(X));
    memset(Y, 0, sizeof(Y));
    memset(ans, 0, sizeof(ans));
    int a, b, d;
    char s[3];
    for(int i = 0;i < M;++i){
        scanf("%d%d%d%s", &a, &b, &d, s);
        //infile >> a >> b >> d >> s;
        int x = 0, y = 0;
        if(s[0] == 'E') x = d;
        else if(s[0] == 'W') x = -d;
        else if(s[0] == 'N')  y = -d;
        else if(s[0] == 'S')  y = d;
        Fa[i] = Farm(a, b, x, y);
    }
    int k;
    scanf("%d", &k);
    //infile >> k;
    for(int i = 0;i < k;++i){
        int pos;
        scanf("%d%d%d", &a, &b, &pos);
        //infile >> a >> b >> pos;
        Q[i] = Query(a, b, pos, i);
    }
    sort(Q, Q+k, cmp);
    int t = 0;
    for(int i = 0;i < M;++i)
    {
        int t1 = find(Fa[i].a);
        int t2 = find(Fa[i].b);
        if(t1 != t2){
            F[t2] = t1;
            X[t2] = X[Fa[i].a] + Fa[i].x - X[Fa[i].b];
            Y[t2] = Y[Fa[i].a] + Fa[i].y - Y[Fa[i].b];
        }
        while(Q[t].pos == i+1 && t < k){
            if(find(Q[t].a) == find(Q[t].b))
                ans[Q[t].index] = abs(X[Q[t].a]-X[Q[t].b])+abs(Y[Q[t].a]-Y[Q[t].b]);
            else 
                ans[Q[t].index] = -1;
            t++;
        }
    }
    for(int i = 0;i < k;++i)
        printf("%d\n", ans[i]);
    //infile.close();
    return 0;
}