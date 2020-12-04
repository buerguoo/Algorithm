/*
Author:buerguoo
Time:936ms
memory:2780Kb

Data:2020-11-27 14:46:57
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
#define FILL(a, b)  memset(a, b, sizeof(a))
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
typedef long long ll;
const int MAXN = 50010;
const int INF = 0x3f3f3f3f;
int sum[MAXN<<2], add[MAXN<<2];
void PushUp(int rt){sum[rt] = sum[rt<<1] + sum[rt<<1|1];}
void build(int l, int r, int rt)
{
    add[rt] = -1;
    if(l == r){
        sum[rt] = 1;
        return ;
    }
    int m = (l+r)>>1;
    build(lson);
    build(rson);
    PushUp(rt);
}
void PushDown(int rt, int ln, int rn)
{
    if(add[rt]!=-1){
        add[rt<<1] = add[rt<<1|1] = add[rt];
        sum[rt<<1] = add[rt]*ln;
        sum[rt<<1|1] = add[rt]*rn;
        add[rt] = -1;
    }
    
}
void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        sum[rt] = C*(r-l+1);
        add[rt] = C;
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  Update(L, R, C, lson);
    if(R > m)   Update(L, R, C, rson);
    PushUp(rt);
}
int Query(int L, int R, int l, int r, int rt)
{
    if(L <= l && R >= r)
        return sum[rt];
    int ans = 0;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m)  ans += Query(L, R, lson);
    if(R > m)   ans += Query(L, R, rson);
    return ans;
}
int BitSearch(int x, int n, int num)
{
    int l = x, r = n;
    int pos;
    while(l <= r){
        int m = (l+r)>>1;
        if(Query(x, m, 0, n, 1) >= num)   r=m-1, pos=m; 
        else l=m+1;
    }
    return pos;
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int T;
    scanf("%d", &T);
    //infile >> T;
    while(T--){
        int n, m;
        scanf("%d%d", &n, &m);
        //infile >> n >> m;
        build(0, n-1, 1);
        int K, A, B;
        while(m--){
            scanf("%d%d%d", &K, &A, &B);
            //infile >> K >> A >> B;
            if(K == 1){
                int cnt = Query(A, n, 0, n-1, 1);
                if(cnt == 0)    printf("Can not put any one.\n");
                else{
                    A = BitSearch(A, n-1, 1);
                    B = BitSearch(A, n-1, min(B, cnt));
                    Update(A, B, 0, 0, n-1, 1);
                    printf("%d %d\n", A, B);
                }
            }
            else{
                printf("%d\n", B-A+1-Query(A, B, 0, n-1, 1));
                Update(A, B, 1, 0, n-1, 1);
            }
        }
        printf("\n");
    }
    //infile.close();

    return 0;
}