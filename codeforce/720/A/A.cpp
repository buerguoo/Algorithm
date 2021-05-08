/*
Time limit:1000ms
Memory limit:256 megabytes

Author:buerguoo
Time:
memory:
WA
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
typedef long long ll;
const int INF = 0x3f3f3f3f;
int main()
{
    int T;
    ll  A, B;
    bool flag;
    scanf("%d", &T);
    while(T--){
        scanf("%lld %lld", &A, &B);
        flag = false;
        if(A == 1 && B != 1){
            printf("YES\n");
            printf("%lld %lld %lld\n", A, A*B, A*(B+1));
            continue;
        }
        for(int i = 1;i < B;++i){
            if(i % A != 0 && (i + B) % A != 0){
                printf("YES\n");
                printf("%lld %lld %lld\n", (ll)i*A, (ll)B*A, (ll)(i+B)*A);
                flag = true;
                break;
            }
            if(i % A != 0 && (B - i) % A != 0){
                printf("YES\n");
                printf("%lld %lld %lld\n", (ll)(B-i)*A, (ll)i*A, (ll)B*A);
                flag = true;
                break;
            }
        }
        if(!flag) printf("NO\n");
    }
    return 0;
}
