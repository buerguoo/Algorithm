#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
//采用线段树动态区间维护
const int MAXN = 10000;
const int MAXM = 500;
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ls(i) i<<1
#define rs(i) i<<1|1

int Pro[MAXM], Start[MAXM];
int pre[MAXN<<2], suf[MAXN<<2], Max[MAXN<<2], add[MAXN];
//��¼�ڴ�ŵ�ʹ�����
bool vis[MAXM];
map<int, int> M;

void PushUp(int rt, int len)
{
    pre[rt] = pre[ls(rt)];
    suf[rt] = suf[rs(rt)];
    if(pre[ls(rt)] == len-(len>>1)) pre[rt] = pre[ls(rt)] + pre[rs(rt)];
    if(suf[rs(rt)] == len>>1) suf[rt] = suf[rs(rt)] + suf[ls(rt)];
    Max[rt] = max(suf[ls(rt)]+pre[rs(rt)], max(Max[ls(rt)], Max[rs(rt)]));
}

void build(int l, int r, int rt)
{
    add[rt]  = -1;
    Max[rt] = pre[rt] = suf[rt] = r-l+1;
    if(l == r) return ;
    int m = (l+r)>>1;
    build(lson);
    build(rson);
}

void PushDown(int rt, int ll, int rl)
{
    if(add[rt]!=-1){
        add[ls(rt)] = add[rs(rt)] = add[rt];
        Max[ls(rt)] = pre[ls(rt)] = suf[ls(rt)] = add[rt]*ll;
        Max[rs(rt)] = pre[rs(rt)] = suf[rs(rt)] = add[rt]*rl;
        add[rt] = -1;
    }
}

void Update(int L, int R, int C, int l, int r, int rt)
{
    if(L <= l && R >= r){
        add[rt] = C;
        Max[rt] = pre[rt] = suf[rt] = C*(r-l+1);
        return ;
    }
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(L <= m) Update(L, R, C, lson);
    if(R > m)   Update(L, R, C, rson);
    PushUp(rt, r-l+1);
}

int Query(int L, int l, int r, int rt)
{
    if(l == r) return l;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    if(Max[ls(rt)] >= L) return Query(L, lson);
    else if(suf[ls(rt)]+pre[rs(rt)] >= L) return m-suf[ls(rt)]+1;
    else if(Max[rs(rt)] >= L) return Query(L, rson);
    else return -1;
}

//�����Ӧ��
int _Query(int L, int l, int r, int rt)
{
    if(l == r) return l;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    int tmp = suf[ls(rt)]+pre[rs(rt)];
    if(Max[ls(rt)] >= tmp && Max[ls(rt)] >= Max[rs(rt)] && Max[ls(rt)] >= L)  
        return Query(L, lson);
    else if(tmp >= Max[ls(rt)] && tmp >= Max[rs(rt)] && tmp >= L) return m-suf[ls(rt)]+1;
    else if(Max[rs(rt)] >= tmp && Max[rs(rt)] >= Max[ls(rt)] && Max[rs(rt)] >= L)
        return Query(L, rson);
    else return -1;
}

void show(int m)
{
    printf("|    进程开始内存\t|    进程大小\t|进程号\t|\n");
    for(int i = 1;i <= m;++i) if(Start[i]){
        printf("*************************************************\n");
        printf("|\t%d\t\t|\t%d\t|   %d\t|\n", Start[i], Pro[i], i);

    }
}

int main()
{
    int n, m;
    printf("请输入内存大小:");
    scanf("%d", &n);
    printf("请输入进程的个数:");    
    scanf("%d", &m);
    build(1, n, 1);
    printf("每个进程占据的内存空间:\n");
    for(int i = 1;i <= m;++i)
        scanf("%d", &Pro[i]);
    
    memset(Start, 0, sizeof(Start));
    memset(vis, false, sizeof(false));
    int choice, a;
    bool b = false;
    getchar();
    printf("选择内存的分配方式:\n1.最先适应法\n2.最佳适应法\n");
    scanf("%d", &a);
    if(a == 1)  b = false;  
    else if(a == 2)  b = true;  
    else{
        printf("请输入合法数据!\n");
        return 0;
    }
    while(1){
        printf("\n输入以下进行选择:\n0.退出\n1.分配内存\n2.释放内存\n3.展示内存空间的");
        printf("使用情况\n4.改变内存分配方式\n5.增加新的进程\n\n");
        scanf("%d", &choice);
        if(choice == 0) break;
        else if(choice == 1) {
            printf("输入分配的进程号:");
            scanf("%d", &a);
            if(vis[a] || a <= 0 || a > m){
                printf("请输入合法数据\n");
                continue;
            }
            int start;
            if(b)  start = Query(Pro[a], 1, n, 1);  
            else start = _Query(Pro[a], 1, n, 1);
            if(start == -1) {printf("没有可分配内存\n"); continue;}
            Start[a] = start;
            Update(start, start+Pro[a]-1, 0, 1, n, 1);
            vis[a] = true;
        }
        else if(choice == 2){
            printf("请输入释放的进程号:");
            scanf("%d", &a);
            if(!vis[a] || a <= 0 || a > m){
                printf("请输入合法数据\n");
                continue;
            }   
            Update(Start[a], Start[a]+Pro[a]-1, 1, 1, n, 1);
            Start[a] = 0;
            vis[a] = false;
        }   
        else if(choice == 3){
            show(m);
        } 
        else if(choice == 4){
            printf("选择内存的分配方式:\n1.最先适应法\n2.最佳适应法\n");            
            scanf("%d", &a);
            if(a == 1)  b = false;  
            else if(a == 2)  b = true;  
            else{
                printf("请输入合法数据！\n");
                return 0;
            }
        }
        else if(choice == 5){
            printf("请输入添加进程的数量");
            int tm;    
            scanf("%d", &tm);
            printf("请输入每个进程占据的内存大小\n");
            for(int i = m+1;i <= m+tm;++i)
                scanf("%d", &Pro[i]);
            m += tm;
        }
        else printf("请输入合法数据!\n");
    }
    
    return 0;
}