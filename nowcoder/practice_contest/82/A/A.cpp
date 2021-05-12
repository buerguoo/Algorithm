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
string s;
int q[MAXN];
char m[6] = "mocha";
bool check(int p)
{
    for(int i = 0;i < 5;++i){
        if(s[p+i] != m[i]) return false;
    }
    return true;
}
int main()
{
    int m = 0, ans = 0;
    int n, k;
    cin >> n >> k;
    cin >> s;
    for(int i = 0;i < n-4;++i){
        if(check(i)) q[m++] = i;
    }
    if(m < k){
        printf("poor Mocha\n");
    }else{
        for(int i = 0;i < m - k + 1;++i)
            ans = min(ans, q[i + k - 1] - q[i] + 5);
        printf("Mocha suki!\n%d\n", ans);
    }
    return 0;
}