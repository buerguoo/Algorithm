#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int INF = 2e9;
char start[10],e[10],path[100];
int M[10],pos_e[10],n,Case,nextd;
char type[5] = "dlru";
int ch[2][4] = {{1,0,0,-1},{0,-1,1,0}};

int get_h(int s[])
{
    int h = 0;
    for(int i = 0;i < 9;i++)
    if(s[i] != 9)
    {
        int x = i / 3,y = i % 3;
        int tx = pos_e[s[i]] / 3,ty = pos_e[s[i]] % 3;
        h += abs(x - tx) + abs(y - ty);
    }
    return h;
}

bool IDAstar(int loc,int depth,int pre,int limit)
{
    int h = get_h(M);
    if(depth + h > limit)
    {
        nextd = min(nextd, depth+h);
        return false;
    }
    if(h == 0)
    {
        path[depth] = '\0';
        printf("Case %d: %d\n",Case, depth);
        puts(path);
        return true;
    }
    int x = loc / 3, y = loc % 3;
    for(int i = 0;i < 4;i++)
    {
        if(pre + i == 3)
            continue;
        int tx = x + ch[0][i],ty = y + ch[1][i];
        if(tx >= 0 && ty >= 0 && tx < 3 && ty < 3){
        int te_loc = tx * 3 + ty;
        path[depth] = type[i];
        swap(M[loc],M[te_loc]);
        if(IDAstar(te_loc, depth+1, i, limit))
            return true;
        swap(M[loc],M[te_loc]);
        }
    }
    return false;
}

int main()
{
    int limit,loc;
    scanf("%d",&n);
    for(Case = 1;Case <= n;++Case)
    {
        scanf("%s",&start);
        for(int i = 0;i < 9;i++)
        {
            if(start[i] == 'X') M[i] = 9,loc = i;
            M[i] = start[i] - '0';
        }
        scanf("%s",e);
        for(int i= 0;i < 9;i++)
        {
            if(e[i] == 'X') pos_e[9] = i;
            pos_e[e[i] - '0'] = i;
        }
        for(limit = get_h(M); ;limit = nextd)
        {
            nextd = INF;
            if(IDAstar(loc, 0, INF, limit))
                break;
        }
    }
}