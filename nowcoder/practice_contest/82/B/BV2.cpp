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
typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 100010;
int main()
{
    int n, m;
    int l, r, k, t;
    scanf("%d %d", &n, &m);
    while(m--){
        scanf("%d", &t);
        if(t == 1) scanf("%d %d", &l, &r);
        else if(t == 2) scanf("%d %d %d", &l, &r, &k);
        else{
            scanf("%d %d", &l, &r);
            printf("0\n");
        }
    }
    return 0;
}