#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
using namespace std;
//FPSA求正环 逆向思维
const int MAXN = 35;
const int INF = 0x3f3f3f3f;

struct Edge{
    int v;
    double rate;
    Edge(int _v, double _r):v(_v), rate(_r){}
    bool operator <(const Edge &r) const{
        return rate < r.rate;
    }
};

vector<Edge> E[MAXN];
bool vis[MAXN];
double dis[MAXN];
int cnt[MAXN];

char name[33][100];
int n;
int tonum(char *str)
{
	for(int i=0;i<n;i++)
	    if(strcmp(str,name[i])==0)
	        return i;
    
    return -1;
}
bool Bellman_ford(int n, int beg)
{
    for(int i = 0;i <= n;++i){
        vis[i] = false;
        dis[i] = 0.0;
        cnt[i] = 0;
    }
    dis[beg] = 1.0;
    vis[beg] = true;
    cnt[beg] = 1;
    queue<int> Q;
    Q.push(beg);
    while(!Q.empty()){
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = 0;i < E[u].size();i++){
            int v = E[u][i].v;
            double r = E[u][i].rate;
            if(dis[v] < dis[u]*r){
                dis[v] = dis[u]*r;
                if(!vis[v]){
                    vis[v] = true;
                    Q.push(v);
                    if(++cnt[v] > n)    return true;
                }
            }  
        }
    }

    return false;
}


int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    //scanf("%d", &n)
    int T = 0;
    while(scanf("%d", &n)!=EOF && n!=0){
        char a[100], b[100];
        double r;
        for(int i = 0;i <= n;++i)    E[i].clear();
        memset(name, 0, sizeof(name));
        for(int i = 0;i < n;++i)
            //infile >> name[i];
            scanf("%s", name[i]);
        int m;
        scanf("%d", &m);
        //infile >> M;
        for(int i = 0;i < m;++i){
            memset(a, 0, sizeof(a));
            memset(b, 0, sizeof(b));
            //infile >> a >> r >> b;
            scanf("%s%lf%s", a, &r, b);
            E[tonum(a)].push_back(Edge(tonum(b), r));
            
        }
        bool ok = false;
        for(int i = 0;i < n;++i)
            if(Bellman_ford(n, i)){
                ok = true;
                break;
            }
        if(ok)  printf("Case %d: YES\n",++T);
        else printf("Case %d: NO\n",++T);
    } 
    //infile.close();

    return 0;
}
