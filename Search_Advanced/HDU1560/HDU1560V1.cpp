#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 8
char str[5] = "AGCT",in[MAXN][10],ans[20],ans_ed[20];
int t,coun,len[MAXN];
int dep,lim;

bool Check(char ans[],int len)
{
    
    
    for(int i = 0;i < coun;++i){
        int k = 0;
        for(int j = 0;j < len;++j)
        {
            if(in[i][k] == ans[j])
                k++;
        }
        if(k < strlen(in[i]))
            return false;
    }
    return true;
}

bool ID(int depth,int limit)
{
    //cout << depth << endl;
    if(limit > 15)
        return false;
    if(depth >= limit && Check(ans,strlen(ans)))
        return true;
    if(depth > limit)
       {
           lim = depth;
           return false;
       } 
    for(int i = 0;i < 4;++i) 
    {
        ans[depth] = str[i];
        if(ID(depth+1,limit))
            return true;
       // ans[depth] = '/0';
    }
    return false;
}
int main()
{
    //TLE
    cin >> t;
    while(t-- > 0){
        bool key;
        cin >> coun;
        for(int i = 0;i < coun;++i)
            {
                cin >> in[i];
                len[i] = strlen(in[i]);
            }
        for(int i = 0;i < coun;++i) lim =max(lim,len[i]);
        while(1){
            if(!ID(lim,lim))
                ID(0,lim);
            else 
                break;
        }
        cout << ans << endl;
        cout << strlen(ans) << endl; 
    }
    return 0;
}