/*
Author:buerguoo
Time:
memory:

Data:
*/
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
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 100010;
map<char, int> M;
char input[MAXN];
int main()
{
    while(~scanf("%s", input)){
        int sz = strlen(input);
        M.clear();
        for(int i = 0;i < sz;++i)
            M[input[i]]++;
        int MAX = 0, k = -1;
        for(int i = 0;i < sz;++i)
            if(MAX <= M[input[i]]){
                MAX = M[input[i]];
                k = i;
                if(MAX == M[input[i]] && input[k] > input[i]) k = i;
            }
        printf("%c\n%d\n", input[k], MAX);
        memset(input, 0, sizeof(input));
    }
    return 0;
}
