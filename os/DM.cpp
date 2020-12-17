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

//���̵��ȵ����ַ�ʽ

int FCFS(int n, int start, int track[])
{
    int res = 0, tmp = start;
    printf("�����ȷ�������㷨��˳��Ϊ:%d ", start);
    for(int i = 0;i < n;++i){
        printf("%d ", track[i]);
        res += abs(tmp-track[i]);
        tmp = track[i];
    }
    printf("\n��Ѱ����Ϊ:%d\n", res);

    return tmp;
}

int SSTF(int n, int start, int track[])
{
    n = unique(track, track+n) - track;
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
    
    printf("��ѡ��Ѱ������:\n1.��С���\n2.�ȴ��С\n");
    scanf("%d", &a);
    if(a == 1) b = false;
    else if(a == 2) b = true;
    else{
        printf("������Ϸ�����!\n");
        return 0;
    }
    int ind = find(temp, temp+n, start) - temp;
    printf("���ݵ����㷨��˳��Ϊ: ");
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

    printf("\n��Ѱ����Ϊ:%d\n", res);

    return tmp;
}

int main()
{
    int start, n, now;
    printf("��������ʼλ�õĴŵ���:\n");
    scanf("%d", &start);
    printf("��������Ҫ���ʵ�������:\n");
    scanf("%d", &n);
    printf("������ʵ����к�:\n");
    for(int i = 0;i < n;++i)
        scanf("%d", &track[i]);
    
    int choice;
    while(1){
        printf("��ѡ��Ѱ����ʽ:\n0.�˳�\n1.�����ȷ���\n2.���Ѱ������\n3.�����㷨\n4.�¼�������\n");
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
            //�����Ҫ���ʵ����к��������ж����£���ͷλ�ø���Ϊ���һ��ʹ���㷨���ȵ�λ��  
            start = now;
            printf("��������Ҫ���ʵ�������:\n");
            scanf("%d", &n);
            printf("������ʵ����к�:\n");
            for(int i = 0;i < n;++i)
                scanf("%d", &track[i]);
            break;
        default:
            break;
        }
    }
    return 0;
}