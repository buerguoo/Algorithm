#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <set>
using namespace std;
//并查集
const int MAXN = 1e5+10;
int F[MAXN];
int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    return F[x] = tmp;
}
int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int u, v, sum=0, K = 0;
    set<int> s;
    memset(F, -1, sizeof(F));
    bool flag = false;
    //~scanf("%d%d", &u, &v)
    while(~scanf("%d%d", &u, &v) && u!=-1 && v!=-1){
        if(u == 0 && v == 0){
            K++;
            if((!flag&&sum+1==s.size())||!sum)    printf("Case %d is a tree.\n", K);
            else printf("Case %d is not a tree.\n", K);
            flag = false;
            memset(F, -1, sizeof(F));
            s.clear();
            sum = 0;
            continue;
        }
        if(!flag){
            sum++;
            s.insert(u);
            s.insert(v);
            int t1 = find(u);
            int t2 = find(v);
            if(t1 != t2)    F[t2] = t1;
            else flag = true;
        }
    }
    //infile.close();
    return 0;
}
