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
char name[3][20] = {"�����ȷ���", "���Ѱ������", "ɨ���㷨"};
//���̵��ȵ����ַ�ʽ

void FCFS(int n, int start, int track[])
{
    int res = 0, tmp = start;
    printf("�����ȷ�������㷨��˳��Ϊ:%d ", start);
    for(int i = 0;i < n;++i){
        printf("%d ", track[i]);
        res += abs(tmp-track[i]);
        tmp = track[i];
    }
    printf("\n��Ѱ����Ϊ:%d\n", res);
}

void SSTF(int n, int start, int track[])
{
    int tmp = start, res = 0, Min = INF, p = -1, m;
    memset(vis, false, sizeof(vis));
    printf("���Ѱ��ʱ�����ȵ����㷨��˳��Ϊ:%d ",start);
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
    printf("\n��Ѱ����Ϊ:%d\n", res);
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
    printf("���ݵ����㷨��˳��Ϊ:%d ", start);
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
    printf("\n��Ѱ����Ϊ:%d\n", res);
}

int main()
{
    int start, n;
    printf("��������ʼλ�õĴŵ���:\n");
    scanf("%d", &start);
    printf("��������Ҫ���ʵ�������:\n");
    scanf("%d", &n);
    printf("������ʵ����к�:\n");
    for(int i = 0;i < n;++i)
        scanf("%d", &track[i]);
    
    FCFS(n, start, track);
    SSTF(n, start, track);
    SCAN(n, start, track);
    return 0;
}