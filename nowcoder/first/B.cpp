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
    int ans;
    void partation(ll x, int dep)
    {
        if(x == 1) {
            ans = dep;
            return ;
        }
        partation(x-x/2, dep+1);
    }
    int main()
    {
        int T;
        ll n;
        scanf("%d", &T);
        while(T--){
            scanf("%lld", &n);
            partation(n, 1);
            printf("%d\n", ans);
        }
        return 0;
    }