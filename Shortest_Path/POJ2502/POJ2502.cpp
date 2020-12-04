#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
const int MAXN = 210;
const double INF = 1e8;
bool vis[MAXN];
double dis[MAXN];
double E[MAXN][MAXN];
struct Edge{
    int u;
    double cost;
    Edge(int _u=0,double _c=0):u(_u), cost(_c){}
    bool operator < (const Edge &r) const{
        return cost > r.cost;
    }
};
struct  Point
{
    int x;
    int y;
}P[MAXN];

double Dis(Point a, int x, int y)
{
    return sqrt(double(a.x-x)*(a.x-x)+double(a.y-y)*(a.y-y));
}

double Dijkstra(int start, int n)
{
    for(int i = 0;i <= n;++i){
        vis[i] = false;
        dis[i] = INF;
    }
    dis[start] = 0;
    priority_queue<Edge> Q;
    Q.push(Edge(start, 0));
    while (!Q.empty())
    {
        Edge tmp = Q.top();
        Q.pop();
        int u = tmp.u;
        if(vis[u])  continue;
        vis[u] = true;
        for(int i = 0;i <= n;i++){
            if(!vis[i] &&  dis[u] + E[u][i] < dis[i]){
                dis[i] = dis[u] + E[u][i];
                Q.push(Edge(i, dis[i]));
            }
        }
    }

    //for(int i = 0;i < n;++i)
        //printf("%lf\n", dis[i]);
    return dis[n]; 
}

int main()
{
    //ifstream infile;
    //infile.open("D://input.txt", ios::in);
    int Ex, Ey;
    scanf("%d%d%d%d",&P[0].x, &P[0].y, &Ex, &Ey);
    //infile >> P[0].x >> P[0].y >> Ex >> Ey; 
    int x, y, x1, y1;
    int count = 0;
    for(int i = 0;i < MAXN;++i){
        for(int j = 0;j < MAXN;++j){
            E[i][j] = INF;
            if(i == j) E[i][j] = 0;
        }
    }
    scanf("%d%d", &x, &y);
    //infile >> x >> y;
    while(scanf("%d%d", &x1, &y1) != EOF){
        P[++count].x = x, P[count].y = y;
        if(x1 == -1 && y1 == -1)  {
            if(scanf("%d%d", &x, &y) != EOF)  continue;
            else break;
        }
        E[count][count+1] = E[count+1][count] = min(Dis(P[count], x1, y1)/2000*3
            , E[count][count+1]);
        x = x1, y = y1;
    }
    P[++count].x = Ex,P[count].y = Ey;
    for(int i = 0;i <= count;++i)
        for(int j = 0;j <= count;++j) 
           E[i][j] = min(Dis(P[i], P[j].x, P[j].y)/500*3, E[i][j]);


    
    printf("%.0lf\n", Dijkstra(0, count));
    //infile.close();
    return 0;
}