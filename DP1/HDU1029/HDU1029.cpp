/*
Time limit:1000ms
Memory limit:32768Kb

Author:buerguoo
Time:187ms
memory:1732kB

Data:2021-04-07 23:15:36
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
const int MAXN = 10010;
const int MAXM = 100010;
int main()
{
    int n, num;
    int cnt, ans;
    while(~scanf("%d", &n)){
        ans = cnt = 0;
        while(n--){
            scanf("%d", &num);
            if(cnt == 0){
                cnt++;
                ans = num;
            }else{
                if(ans == num) cnt++;
                else cnt--;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}