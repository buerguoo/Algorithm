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
const int MAXN = 100010;
const int MAXM = 100010;
int F[MAXN] = {0}, C[MAXN] = {0};
int main()
{
    int n, q;
    int a, x;
    int head = 1, cur, tp;
    scanf("%d %d", &n, &q);
    for(int i = 1;i < n;++i){ 
        F[i] = i+1;
        C[i+1] = i;
    }
    while(q--){
        scanf("%d %d", &a, &x);
        tp = a;
        cur = C[a];
        while(F[a] && x--) a = F[a];
        if(tp == head) continue;
        F[cur] = F[a];
        if(F[a]) C[F[a]] = cur;
        F[a] = head, C[head] = a;
        C[head = tp] = 0;
    }
    while(head){
        printf("%d ", head);
        head = F[head];
    }
    return 0;
}