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
const int MAXN = 62;
const int MAXM = 100010;
map<char, int> M;
string s;
int main()
{
    cin >> s;
    int ans = 0;
    int len = s.length();
    for(int i = 0;i < len;++i)  M[s[i]]++;
    if(len > MAXN){
        printf("-1\n");
    }else{
        while(true){
            for(int i = 0;i < len;++i){
                if(M[s[i]] != 1){
                    
                }
            }
        }
    }
    return 0;
}