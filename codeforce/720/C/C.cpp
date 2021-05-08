/*
Time limit:1000ms
Memory limit:32768kb

Author:buerguoo
Time:249ms
memory:3700kb

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
const int MAXN = 10010;
const int MAXM = 100010;
int a[MAXN], n;
int query(int i)
{
    int d;
    cout << "? 1 " << i << " " << i+1 << " " << n-1 << endl;
    cin >> d;
    if(d == n) return i+1;
    else if(d == n-1){
        cout << "? 1 " << i+1 << " " << i << " " << n-1 << endl;
        cin >> d;
        if(d == n) return i;
    }
    return 0;
}
int maxInd()
{
    int x;
    for(int i = 1;i <= n-1;i += 2){
        int x = query(i);
        if(x > 0) return x;
    }   
    return n;
}
int main()
{
    cin.tie(0) -> sync_with_stdio(0);
    int T, m;
    cin >> T;
    while(T--){
        cin >> n;
        m = maxInd();
        for(int i = 1;i <= n;++i){
            if(i == m) continue;
            cout << "? 2 " << i << " " << m << " 1" << endl;
            cin >> a[i];
        }
        a[m] = n;
        cout << "!";
        for(int i = 1;i <= n;++i) cout << " " << a[i];
         cout << endl;
    }
    return 0;
}