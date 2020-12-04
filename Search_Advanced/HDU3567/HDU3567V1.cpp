
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
int has[9];
const int MAXN = 362880;
bool jud[MAXN];
int ch[2][4] = {{1,0,0,-1},{0,1,-1,0}};
char prim[9],prim_2[9];
string ans = "";

struct Node
{
    int g,h,pos;
    int hash_num;
    int num[9];

    bool operator<(const Node c)const
    {
        return h + g >= c.h + c.g;
    }    //对<重载，在使用 优先队列（默认为大顶堆）时首先得到h+g最小的结点

   int get_hash()
    {
        int co = 0;
        hash_num = 0;
        for(int i = 0;i < 9;i++)
        {
            co = 0;
            for(int j = i+1;j < 9;j++)
            {
                if(num[i] > num[j]) co++;
            }
            hash_num += co * has[8-i];
        }
        return hash_num;
    }

    void get_h()
    {
        h = 0;
        for(int i = 0;i < 9;i++)
            h += abs(i - num[i] + 1);
    }

    bool equal_(const Node c)
    {
        return hash_num == c.hash_num;
    }
}S,E;

struct tree
{
    int par;
    char path;
}Tree[MAXN];

int Change(int *num,char *prim)
{
    int pos;
    for(int i = 0;i < 9;i++)
    {
        if(prim[i] != 'X')
            num[i] = prim[i] - '0';
        else 
            {
                num[i] = 9;
                pos = i;
            }
    }
    return pos;
}

int print_ans(int num)
{
    int k = 0;
    ans = "";
    while(Tree[num].par != -1)
   {
       k++;
       ans = Tree[num].path + ans;
       num = Tree[num].par;
   } 
   return k;
}

int A_star()
{
    int tx = 0,ty = 0;
    char type[5] = "drlu";
    if(S.equal_(E)) return 1;
    priority_queue<Node> Q;
    jud[S.hash_num] = 1;
    Tree[S.hash_num].par = -1;
    Q.push(S);
    while(!Q.empty())
    {
        Node next = Q.top();
        Q.pop();
        for(int i = 0;i < 4;i++)
        {
            tx = next.pos / 3 + ch[0][i];
            ty = next.pos % 3 + ch[1][i];
            if(tx < 0 || ty < 0 || tx > 2 || ty > 2)
                continue;
            Node HH = next;
            HH.pos = tx * 3 + ty;
            swap(HH.num[HH.pos],HH.num[next.pos]);
            HH.get_hash();
            if(jud[HH.hash_num]) continue;
            HH.g++;
            HH.get_h();
            jud[HH.hash_num] = 1;
            Tree[HH.hash_num].par = next.hash_num;
            Tree[HH.hash_num].path = type[i];
            Q.push(HH);
            if(HH.equal_(E))   return 1;

        }

    }
    return 0;
}

int main()
{
    int n,p;
    cin >> n;
    p = 1;
    while(p < n+1){
    int key = 0;
    cin >> prim;
    cin >> prim_2;
    memset(jud,0,sizeof(jud));
    has[0] = 1;
    for(int i = 1;i < 9;i++)
        has[i] = has[i-1] * i;
    S.pos = Change(S.num,prim);
    E.pos = Change(E.num,prim_2);
    S.g = 0;
    S.get_h();
    S.get_hash();
    E.get_hash();
    key = A_star();
    if(!key)
        cout <<"unsovable" << endl;
    else{
    cout << "case " << p <<":" << print_ans(E.hash_num) << endl;
    cout << ans << endl;
    }
    ++p;
    }
    return 0;
}