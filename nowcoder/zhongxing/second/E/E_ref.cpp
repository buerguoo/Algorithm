#include<cmath>
#include<iostream>
#include<sstream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<istream>
#include<vector>
#include<stack>
#include<set>
//#include<unordered_map>
#include<map>
#include<algorithm>
#include<queue>
#define mmp make_pair
#define inf 0x3f3f3f3f
#define llinf 0x7fffffffffffffff
using namespace std;
typedef long long  ll;
typedef pair<int,int> PP;
typedef double lld;
const double eps=1e-6;
const int mod=1e9+7;
 
ll a[210][210]={0};
ll w[210];
ll dp[210][210]={0};//第i个商品 移除前j个的最大值
int main() {
    int n,k,m;
    scanf("%d %d %d",&n,&k,&m);
    for(int i=1;i<=m;++i) {
        scanf("%lld",&w[i]);
    }
    for(int i=1;i<=n;++i) {
        for(int j=1;j<=n;++j)
        scanf("%lld",&a[i][j]);
    }
    ll ans=0;
    for(int i=1;i<=m;++i) {
        for(int j=0;j<=k;++j) {//以i结束 总共j个被移除
            if(i-j<0) break;
            for(int kk=0;kk<=j;++kk) {//i 前kk个被移除
                int pre=i-1-kk;
                if(pre<0) break;
                dp[i][j]=max(dp[i][j],dp[pre][j-kk]+a[w[pre]][w[i]]);
                ans=max(ans,dp[i][j]);
            }
        }
    }
 
    printf("%lld",ans);
    return 0;
}