#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//并查集
//阿这...
//WA
const int MAXN = 30010;
const int MAXM = 600;
int pre[MAXN];
bool join[MAXM][MAXM] = {false};
int num[MAXM];
bool vis[MAXM];
int n, m;

int count(int s)
{
    int ans = 0;
    queue<int> Q;
    memset(vis, 0, sizeof(vis));
    Q.push(abs(pre[s]));
    while(!Q.empty()){
        int head = Q.front();
        Q.pop();
        vis[head] = true;
        ans += num[head];
        for(int i = 1;i <= m;++i)
            if(join[head][i] && !vis[i])   
                Q.push(i);
    }
    if(ans == 0)    ans = 1;

    return  ans;
}

int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    //
    while(~scanf("%d%d", &n, &m)){
        if(n == 0 && m == 0)    break;
        for(int i = 0;i < n;++i)    pre[i] = i;
        memset(join, 0, sizeof(join));
        memset(num, 0, sizeof(num));
        for(int t = 1;t <= m;t++){
            int k;
            scanf("%d", &k);
            //infile >> k;
            for(int i = 0;i < k;i++){
                int s;
                scanf("%d", &s);
                //infile >> s;
                if(pre[s] == s) {pre[s] = -t;  num[t]++;}
                else   join[abs(pre[s])][t] = join[t][abs(pre[s])] = true;
            }
        }
        printf("%d\n", count(0));
    }
    //infile.close();
    return 0;
}