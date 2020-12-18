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
//??????????????
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
    //如果查询区间[L, R]包含结点区间[l, r]
    //则修改该节点以及惰性标记
    if(L <= l && R >= r){
        add[rt] = C;
        Max[rt] = pre[rt] = suf[rt] = C*(r-l+1);
        return ;
    }
    int m = (l+r)>>1;
    //惰性标记下移
    PushDown(rt, m-l+1, r-m);
    //查询区间[L, R]左端点小于左结点右端点
    //说明区间与节点区间有重合部分，递归调用
    if(L <= m)  Update(L, R, C, lson);
    //查询区间[L, R]右端点大于右结点左端点
    if(R > m)   Update(L, R, C, rson);
    PushUp(rt, r-l+1);
}

int Query(int L, int l, int r, int rt)
{
    //查询到叶子节点，返回
    if(l == r) return l;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    //按左中右的顺序查找，最先适应
    if(Max[ls(rt)] >= L) return Query(L, lson);
    else if(suf[ls(rt)]+pre[rs(rt)] >= L) return m-suf[ls(rt)]+1;
    else if(Max[rs(rt)] >= L) return Query(L, rson);
    else return -1;
}

int _Query(int L, int l, int r, int rt)
{
    if(l == r) return l;
    int m = (l+r)>>1;
    PushDown(rt, m-l+1, r-m);
    int tmp = suf[ls(rt)]+pre[rs(rt)];
    //满足它最大且适应区间，最佳适应
    if(Max[ls(rt)] >= tmp && Max[ls(rt)] >= Max[rs(rt)] && Max[ls(rt)] >= L)  
        return Query(L, lson);
    else if(tmp >= Max[ls(rt)] && tmp >= Max[rs(rt)] && tmp >= L) return m-suf[ls(rt)]+1;
    else if(Max[rs(rt)] >= tmp && Max[rs(rt)] >= Max[ls(rt)] && Max[rs(rt)] >= L)
        return Query(L, rson);
    else return -1;
}

void show(int m)
{
    printf("|Process start memory|Process size|Process number|\n");
    for(int i = 1;i <= m;++i) if(Start[i]){
        printf("*************************************************\n");
        printf("|\t%d\t     |\t%d\t  |\t  %d\t|\n", Start[i], Pro[i], i);

    }
}

int main()
{
    int n, m;
    printf("Please enter the size of the memory:");
    scanf("%d", &n);
    printf("Please enter the number of processes:");    
    scanf("%d", &m);
    build(1, n, 1);
    printf("Memory space occupied by each process:\n");
    for(int i = 1;i <= m;++i)
        scanf("%d", &Pro[i]);
    
    memset(Start, 0, sizeof(Start));
    memset(vis, false, sizeof(false));
    int choice, a;
    bool b = false;
    getchar();
    printf("Select how to allocate memory:\n1.First adaptation\n2.Best fit method\n");
    scanf("%d", &a);
    if(a == 1)  b = false;  
    else if(a == 2)  b = true;  
    else{
        printf("Please input legal data!\n");
        return 0;
    }
    while(1){
        printf("\nEnter the following to select:\n0.exit\n1.allocate\n2.release\n3.show");
        printf("\n4.Changing memory allocation\n5.Add new process\n\n");
        scanf("%d", &choice);
        if(choice == 0) break;
        else if(choice == 1) {
            printf("Enter the assigned process number:");
            scanf("%d", &a);
            if(vis[a] || a <= 0 || a > m){
                printf("Please input legal data!\n");
                continue;
            }
            int start;
            if(!b)  start = Query(Pro[a], 1, n, 1);  
            else start = _Query(Pro[a], 1, n, 1);
            if(start == -1) {printf("There is no memory to allocate\n"); continue;}
            Start[a] = start;
            Update(start, start+Pro[a]-1, 0, 1, n, 1);
            vis[a] = true;
        }
        else if(choice == 2){
            printf("Please enter the released process number:");
            scanf("%d", &a);
            if(!vis[a] || a <= 0 || a > m){
                printf("Please input legal data!\n");
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
            printf("Select how to allocate memory:\n1.First adaptation\n2.Best fit method\n");            
            scanf("%d", &a);
            if(a == 1)  b = false;  
            else if(a == 2)  b = true;  
            else{
                printf("Please input legal data!\n");
                return 0;
            }
        }
        else if(choice == 5){
            printf("Please enter the number of added processes");
            int tm;    
            scanf("%d", &tm);
            printf("Please enter the amount of memory occupied by each process\n");
            for(int i = m+1;i <= m+tm;++i)
                scanf("%d", &Pro[i]);
            m += tm;
        }
        else printf("Please input legal data!\n");
    }
    
    return 0;
}