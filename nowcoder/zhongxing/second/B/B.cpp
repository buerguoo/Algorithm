#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int MAXN = 100010;
const int MAXM = 100010;
bool used[62] = {0};
int char2num(char c)
{
    if(c >= 'a' && c <= 'z')    return (c - 'a');
    else if(c >= 'A' && c <= 'Z') return (26 + c - 'A');
    else return (52 + c - '0');
}
int main()
{
    int n;
    int ans = 0;
    int cur = 0;
    char ch;
    scanf("%d", &n);
    getchar();
    if(n > 62){
        ans = -1;
    }else{
        for(int i = 0;i < n;++i){
            scanf("%c", &ch);
            cur = char2num(ch);
            while(used[cur]){
                cur =  (cur + 1) % 62;
                ans++;
            }
            used[cur] = true;
        }
    }
    printf("%d\n", ans);
    return 0;
}