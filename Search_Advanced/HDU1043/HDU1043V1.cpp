#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int MAXN = 362880;
int array[10],has[10];
bool jud[MAXN];
int ch[2][4] = {{1,0,0,-1},{0,1,-1,0}};
char prim[9];

struct node1
{
    int par;
    char pt;
};
node1 path[MAXN];
struct node 
{
    int val;
    int index;
    string tar;
    int num[9];
};

int Change()
{
    for(int i = 0;i < 9;i++)
    {
        if(prim[i] != 'x')
            array[i] = prim[i] - '0';
        else 
        array[i] = 9;
    }
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
    char type[5] = "ulrd";
    memset(jud,0,sizeof(jud));
    node next,a;
    for(int i = 0;i < 9;i++)
        a.num[i] = i + 1;
    a.val = Contor(a.num);
    jud[a.val] = 1;
    a.index = 8;
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
            if(!jud[a.val]){
            jud[a.val] = 1;
            a.index = temp;
            path[a.val].par = next.val;
            path[a.val].pt = type[i];
            Q.push(a);
            }
        }

    }
    return 0;

}

int main()
{   
    int i,key;
    string ans = "";
    has[0] = 1;
    for(i = 1;i < 9;++i)
        has[i] = has[i-1] * i;
    Bfs();
    while(cin >> prim[0]){
    ans = "";
    for(i = 1;i < 9;++i)
        cin >> prim[i];
    Change();
    key = Contor(array);
    if(!jud[key])
        cout << "unsolvable" << endl;
    else 
        {
            while(key>0){
            ans = ans + path[key].pt;
            key = path[key].par;
            }
            cout << ans <<  endl;
        }  
    }                         
    return 0;
}