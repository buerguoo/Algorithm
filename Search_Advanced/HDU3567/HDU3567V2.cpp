#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN = 362880;
int array[10],has[10];
bool jud[9][MAXN];
char eight_num[9][10] = {"X12345678","1X2345678","12X345678","123X45678","1234X5678","12345X678",
                         "123456X78","1234567X8","12345678X"};
int ch[2][4] = {{1,0,0,-1},{0,-1,1,0}};
char start[10],end_[10];
int s[10],e[10];

struct node1
{
    int par;
    char pt;
};
node1 path[9][MAXN];
struct node 
{
    int val;
    int index;
    string tar;
    int num[9];
};

int Change(char *prim)
{
    for(int i = 0;i < 9;i++)
    {
        if(prim[i] != 'X')
            array[i] = prim[i] - '0';
        else 
            array[i] = 9;
    }
    for(int i = 0;i < 9;i++)
    return 0;
}

 int Contor(int *array)
{
    
    int co = 0,a = 0;
    for(int i = 0;i < 9;++i)
    {
        co = 0;
        for(int j = i+1;j < 9;j++){
            if(array[i] > array[j]) co++;
        }
        a += co * has[8-i];
    }
    return a;
}

int Bfs()
{
    queue<node> Q;
    int tx,temp,ty;
    char type[5] = "dlru";
    memset(jud,0,sizeof(jud));
    node next,a;
    for(int j = 0;j < 9;j++){
        Change(eight_num[j]);
    for(int i = 0;i < 9;i++)
        a.num[i] = array[i];
    a.val = Contor(a.num);
    jud[j][a.val] = 1;
    path[j][a.val].par = -1;
    path[j][a.val].pt = type[4];
    a.index = j;
    Q.push(a);
    while(!Q.empty()){
        next = Q.front();
        Q.pop();
        for(int i = 0;i < 4;++i)
        {
            tx = next.index / 3 + ch[0][i];
            ty = next.index % 3 + ch[1][i];
            if(tx < 0 ||  ty < 0 || tx > 2 || ty > 2)
                continue;
            a = next;
            temp = tx * 3 + ty;
            a.num[next.index] = a.num[temp];
            a.num[temp] = 9;
            a.val = Contor(a.num);
            if(!jud[j][a.val]){
            jud[j][a.val] = 1;
            a.index = temp;
            path[j][a.val].par = next.val;
            path[j][a.val].pt = type[i];
            Q.push(a);
            }
        }
    }
    }
    return 0;

}

int main()
{   
    int i,key,n,p,ind;
    int t,z;
    string ans = "";
    has[0] = 1;
    for(i = 1;i < 9;++i)
        has[i] = has[i-1] * i;
    Bfs();
    cin >> n;
    p = 1;
    while(p <= n){
    ans = "";
    t = 1;
    z = 0;
    cin >> start;
    for(i = 0;i < 9;i++)
    {
        if(start[i] == 'X') ind = i;
        else s[start[i] - '0'] = t++;
    }
    cin >> end_;
    for(i = 0;i < 9;i++)
    {   
         if(end_[i] == 'X') e[i] = 9;
         else e[i] = s[end_[i] - '0'];
    }
    key = Contor(e);
    while(key > -1){
            if(path[ind][key].pt != '\0')
            ans = path[ind][key].pt + ans;
            key = path[ind][key].par;
            z++;
            }
        cout << "Case " << p << ": " << z-1 << endl;
        cout << ans <<  endl;
    ++p;  
    }                         
    return 0;
}