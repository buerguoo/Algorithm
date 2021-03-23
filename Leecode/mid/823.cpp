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
class Solution {
public:
    const int MOD = 1000000007;
    int numFactoredBinaryTrees(vector<int>& arr) {
        int sz = arr.size();
        sort(arr.begin(), arr.end());       
        map<long, long> m;
        long res = 0;
        for(int i = 0;i < sz;++i){
            m[arr[i]] = 1;
            for(int j = 0;j < i;++j){
                int q = arr[i] / arr[j];
                int md = arr[i] % arr[j];
                if(q < arr[j]) break;
                if(md == 0 && m.find(q) != m.end())
                    m[arr[i]] += (arr[j] == q) ? m[arr[j]]*m[q] : m[arr[j]]*m[q]*2;
            }
        }
        for(auto mp:m) res += mp.second;
        return res%MOD;
    }
};