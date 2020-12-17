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
bool vis[MAXN];
int track[MAXN], temp[MAXN];

//磁盘调度的三种方式

int FCFS(int n, int start, int track[])
{
    int res = 0, tmp = start;
    printf("先来先服务调度算法的顺序为:%d ", start);
    for(int i = 0;i < n;++i){
        printf("%d ", track[i]);
        res += abs(tmp-track[i]);
        tmp = track[i];
    }
    printf("\n总寻道数为:%d\n", res);

    return tmp;
}

int SSTF(int n, int start, int track[])
{
    n = unique(track, track+n) - track;
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

    return tmp;
}

int SCAN(int n, int start, int track[])
{
    n = unique(track, track+n) - track;
    int tmp = start, res = 0, a;
    bool b = false;
    for(int i = 0;i < n;++i)
        temp[i] = track[i];
    temp[n++] = start;
    sort(temp, temp+n);
    
    printf("请选择寻道方向:\n1.先小后大\n2.先大后小\n");
    scanf("%d", &a);
    if(a == 1) b = false;
    else if(a == 2) b = true;
    else{
        printf("请输入合法数据!\n");
        return 0;
    }
    int ind = find(temp, temp+n, start) - temp;
    printf("电梯调度算法的顺序为: ");
    if(!b){
        for(int i = ind;i > 0;--i){
            printf("%d ", temp[i]);
            res += temp[i] - temp[i-1];
        }
        printf("%d ", temp[0]);
        res += (temp[ind+1] - temp[0]);
        for(int i = ind+1;i < n-1;++i){
            printf("%d ", temp[i]);
            res += temp[i+1] - temp[i];
        }
        printf("%d ", temp[n-1]);
        tmp = temp[n-1];
    }
    else{
        for(int i = ind;i < n-1;++i){
            printf("%d ", temp[i]);
            res += temp[i+1] - temp[i];
        }
        printf("%d ", temp[n-1]);
        res += (temp[n-1] - temp[ind-1]);
        for(int i = ind-1;i > 0;--i){
            printf("%d ", temp[i]);
            res += temp[i] - temp[i-1];
        }
        printf("%d ", temp[0]);
        tmp = temp[0];
    }

    printf("\n总寻道数为:%d\n", res);

    return tmp;
}

int main()
{
    int start, n, now;
    printf("请输入起始位置的磁道号:\n");
    scanf("%d", &start);
    printf("请输入需要访问的序列数:\n");
    scanf("%d", &n);
    printf("输入访问的序列号:\n");
    for(int i = 0;i < n;++i)
        scanf("%d", &track[i]);
    
    int choice;
    while(1){
        printf("请选择寻道方式:\n0.退出\n1.先来先服务\n2.最短寻道优先\n3.电梯算法\n4.新加入序列\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
                now = FCFS(n, start, track);
            break;
        case 2:
                now = SSTF(n, start, track);
            break;
        case 3:
                now = SCAN(n, start, track);
            break;
        case 0:
                return 0;
            break;
        case 4:
            //添加想要访问的序列后，整个序列都更新，磁头位置更新为最后一次使用算法调度的位置  
            start = now;
            printf("请输入需要访问的序列数:\n");
            scanf("%d", &n);
            printf("输入访问的序列号:\n");
            for(int i = 0;i < n;++i)
                scanf("%d", &track[i]);
            break;
        default:
            break;
        }
    }
    return 0;
}