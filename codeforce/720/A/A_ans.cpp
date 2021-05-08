/*
Time limit:1000ms
Memory limit:256 megabytes

Author:buerguoo
Time:31ms
memory:3600KB

Data:May/08/2021 09:13
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
typedef long long ll;
const int INF = 0x3f3f3f3f;
int main()
{
    
    int T;
    ll A, B;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%lld %lld", &A, &B);
        if(B == 1){
            printf("NO\n");
        }else{
            printf("YES\n");
            printf("%lld %lld %lld\n", A, A*(ll)B, A*(ll)(B+1));
        }
    }
    return 0;
}