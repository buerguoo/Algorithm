#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int coun,an[10],depth=0;
char con[5] = "AGCT";

struct Node{
    string s;
    int len;
}Str[10];

int get()
{
    int ans = 0;
    for(int i = 0;i < coun;i++)
        ans = max(ans,Str[i].len-an[i]);
    return ans;
}

int IDA(int pos)
{
    int flag;
    if(get()+pos > depth) return 0;
    if(!get()) return 1;
    int temp[10];
    for(int i =0;i < coun;++i) temp[i] = an[i];
    for(int i = 0;i < 4;++i)
    {
        flag = 0;
        for(int j=0;j < coun;++j)
        {
            if(con[i] == Str[j].s[an[j]])
               {
                    an[j]++;
                    flag = 1;
               } 
        }
        if(flag)
        {
            if(IDA(pos+1))
                return 1;
             for(int i =0;i < coun;++i) an[i] = temp[i];
        }
    }
    return 0;
}

int main()
{
    int t;
    cin >> t;
    while(t-- > 0){
        cin >> coun;
        memset(an,0,sizeof(an));
        for(int i = 0;i < coun;++i)
        {
            cin >> Str[i].s;
            Str[i].len = Str[i].s.length();
        }
    for(int i=0;i < coun;++i) depth=max(depth,Str[i].len);
    while(1){
        if(IDA(0))
            break;
        depth++;
    }
    cout << depth << endl;
}
return 0;
}