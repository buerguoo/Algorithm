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
const int MAXN = 10010;
int F[MAXN], val[MAXN],p[MAXN];
map<pair<int, int>, int>  Hash;
struct query 
{
    int s, t;
    bool flag;
}Q[MAXN*5];
void Init(int n)
{
    for(int i = 0;i < n;++i){
        F[i] = -1;
        val[i] = p[i];
    }
}
int find(int x)
{
    if(F[x] == -1)     return x;
    int tmp = find(F[x]);
    val[x] = max(val[x], val[F[x]]);
    return F[x] = tmp;
}
void _union(int a, int b)
{
    int t1 = find(a);
    int t2 = find(b);
    if(t1 == t2)    return;
    if(val[t1]>val[t2] || (val[t1]==val[t2]&&t1<t2))    F[t2] = t1;
    else F[t1] = t2;
}
int main()
{
    int n, tag = 0;
    while (~scanf("%d", &n))
    {
        if(tag++)   printf("\n");
        for(int i = 0;i < n;++i)    scanf("%d", &p[i]);
        Hash.clear();
        Init(n);
        int m, a, b;
        scanf("%d", &m);
        for(int i = 0;i < m;++i){
            scanf("%d%d", &a, &b);
            if(a>b) swap(a, b);
            Hash[make_pair(a, b)] = 1;
        }
        char s[10];
        int q;
        scanf("%d", &q);
        for(int i = 0;i < q;++i){
            scanf("%s", s);
            if(s[0] == 'q'){
                scanf("%d", &Q[i].s);
                Q[i].flag = false;
            }
            else{
                int a, b;
                scanf("%d%d", &a, &b);
                if(a > b)   swap(a, b);
                Q[i].s = a, Q[i].t = b, Q[i].flag = true;
                Hash[make_pair(a, b)] = 0;
            }
        }
        for(map<pair<int, int>, int>::iterator it=Hash.begin();it!=Hash.end();it++){
            if(it->second){
                pair<int, int>  tmp = it->first;
                _union(tmp.first, tmp.second);
            }
        }
        vector<int> v;
        v.clear();
        for(int i = q-1;i >= 0;--i){
            if(Q[i].flag){
                _union(Q[i].s, Q[i].t);
            }
            else{
                int x = Q[i].s;
                int t = find(x);
                if(val[t] > p[x])    v.push_back(t);
                else v.push_back(-1);
            }
        }
        for(int i = v.size()-1;i >= 0;--i)
            printf("%d\n", v[i]);
    }
    
    return 0;
}
