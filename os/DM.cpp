# include <iostream>
# include <cstdio>
# include <algorithm>
# include <cstring>
# include <vector>
# include <map>
# include <queue>
using namespace std;
const int MAXN = 1000;
const int INF = 0x3f3f3f3f;
int track[MAXN];
bool vis[MAXN];
char name[3][20] = {"先来先服务", "最短寻道调度", "扫描算法"};
//磁盘调度的三种方式

void FCFS(int n, int start, int track[])
{
    int res = 0, tmp = start;
    printf("先来先服务调度算法的顺序为:%d ", start);
    for(int i = 0;i < n;++i){
        printf("%d ", track[i]);
        res += abs(tmp-track[i]);
        tmp = track[i];
    }
    printf("\n总寻道数为:%d\n", res);
}

void SSTF(int n, int start, int track[])
{
    int tmp = start, res = 0, Min = INF, p = -1, m;
    memset(vis, false, sizeof(vis));
    printf("最短寻道时间优先调度算法的顺序为:%d ",start);
    for(int i = 0;i < n;++i){
        Min = INF;
        for(int j = 0;j < n;++j)
            if(!vis[j] && abs(tmp-track[j]) < Min){
                Min = abs(tmp-track[j]);
                p = j;
            }
        vis[p] = true;
        tmp = track[p];
        printf("%d ", tmp);
        res += Min;
    }
    printf("\n总寻道数为:%d\n", res);
}

void SCAN(int n, int start, int track[])
{
    int tmp = start, res = 0;
    priority_queue<int> Q1;
    priority_queue<int, vector<int>, greater<int> > Q2;
    for(int i = 0;i < n;++i){
        if(track[i] <= start) Q1.push(track[i]);
        else Q2.push(track[i]);
    }
    printf("电梯调度算法的顺序为:%d ", start);
    while(!Q1.empty()){
        int q = Q1.top();
        Q1.pop();
        printf("%d ", q);
        res += abs(tmp - q);
        tmp = q;
    }
    while (!Q2.empty())
    {
        int q = Q2.top();
        Q2.pop();
        printf("%d ", q);
        res += abs(q - tmp);
        tmp = q;
    }
    printf("\n总寻道数为:%d\n", res);
}

int main()
{
    int start, n;
    printf("请输入起始位置的磁道号:\n");
    scanf("%d", &start);
    printf("请输入需要访问的序列数:\n");
    scanf("%d", &n);
    printf("输入访问的序列号:\n");
    for(int i = 0;i < n;++i)
        scanf("%d", &track[i]);
    
    FCFS(n, start, track);
    SSTF(n, start, track);
    SCAN(n, start, track);
    return 0;
}