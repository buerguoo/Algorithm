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
const int MAXN = 300010;
const int MAXM = 100010;
struct children{
    int t, d, h, ind;
    bool operator<(const children &a){
        return t < a.t;
    }
};
vector<children> chi;
pii q[MAXN];
vi ans;
int main()
{   
    int n, t, d, h;
    scanf("%d", &n);
    for(int i = 0;i < n;++i){
        scanf("%d %d %d", &t, &h, &d);
        chi.push_back({t, d, h, i});
    } 
    sort(chi.begin(), chi.end());
    ans.resize(n);
    int cnt = 0, l, r, mid;
    for(int i = 0;i < n;++i){
        l = 0, r = cnt;
        while(l < r){
            mid = (l + r) / 2;
            if(q[mid].first >= chi[i].t - chi[i].d)   r = mid;
            else l = mid + 1;
        }
        ans[chi[i].ind] += (cnt - l);
        while(cnt > 0 && q[cnt-1].second <= chi[i].h) cnt--;
        q[cnt] = {chi[i].t, chi[i].h};
        cnt++;
    }
    cnt = 0;
    for(int i = n-1;i >= 0;--i){
        l = 0, r = cnt;
        while(l < r){
            mid = (l + r) / 2;
            if(q[mid].first <= chi[i].t + chi[i].d) r = mid;
            else l = mid + 1;
        }
        ans[chi[i].ind] += (cnt - l);
        while(cnt > 0 && q[cnt-1].second <= chi[i].h) cnt--;
        q[cnt] = {chi[i].t, chi[i].h};
        cnt++;
    }
    for(int i = 0;i < n;++i){
        if(i) printf(" ");
        printf("%d", ans[i]);
    }
    return 0;
}