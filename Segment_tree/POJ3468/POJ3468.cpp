/*
Author:buerguoo
name:POJ3468
Time:1250ms
memory:4800KB

Data:2020-11-22 22:51:39
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
const int MAXN = 1e5+10;
int n, N;
long long int A[MAXN];
long long int sum[MAXN<<2], add[MAXN<<2];
void build(int n)
{
    N = 1;
    while(N < n+2)  N <<= 1;
    for(int i = 1;i <= n;++i)   sum[N+i] = A[i];
    for(int i = N-1;i > 0;i--){
        sum[i] = sum[i<<1] + sum[i<<1|1];
        add[i] = 0;
    } 
}
void Update(int L, int R, int C)
{
    int s, t, ln = 0, rn = 0, x = 1;
    for(s=L+N-1, t=R+N+1;s^t^1;s>>=1, t>>=1, x<<=1){
        sum[s] += C*ln;
        sum[t] += C*rn;
        if(~s&1)  add[s^1]+=C, sum[s^1]+=x*C, ln+=x;
        if( t&1)  add[t^1]+=C, sum[t^1]+=x*C, rn+=x;
    }
    for(;s;s>>=1, t>>=1){
        sum[s] += C*ln;
        sum[t] += C*rn;
    }
}
long long int Query(int L, int R)
{
    int s, t, ln=0, rn=0, x=1;
    long long int ans = 0;
    for(s=L+N-1, t=R+N+1;s^t^1;s>>=1, t>>=1, x<<=1){
        if(add[s])  ans += add[s]*ln;
        if(add[t])  ans += add[t]*rn;
        //printf("<<<<<<<<<<\n");
        if(~s&1)    ans += sum[s^1], ln+=x;
        if( t&1)    ans += sum[t^1], rn+=x;
    }
    for(;s;s>>=1, t>>=1){
        ans += add[s]*ln;
        ans += add[t]*rn;
    }

    return ans;
}
int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    for(int i = 1;i <= N;i++)   scanf("%lld", &A[i]);
    build(N);
    char s[2];
    int a, b, c;
    for(int i = 0;i < Q;++i)
    {
        scanf("%s", s);
        if(s[0] == 'Q'){
            scanf("%d%d", &a, &b);
            printf("%lld\n", Query(a, b));
        } 
        else if(s[0] == 'C'){
            scanf("%d%d%d", &a, &b, &c);
            Update(a, b, c);
        }
    }

    return 0;
}
