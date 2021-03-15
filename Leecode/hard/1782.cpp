#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> du(n);
        map<pii,int> mp;
        for (vector<int> &i:edges) {
            int u=i.at(0)-1,v=i.at(1)-1;
            du.at(u)++;
            du.at(v)++;
            if (u>v) {
                swap(u,v);
            }
            mp[{u,v}]++;
        }
        vector<int> sortDu(du);
        sort(sortDu.begin(),sortDu.end());
        int queSz=queries.size();
        vector<int> ans(queSz);
        for (int i=0;i<queSz;i++) {
            int upper=0;
            int que=queries.at(i);
            int l=0,r=n-1;
            for (l=0;l<n-1;++l) {
                while (l<r && sortDu.at(l)+sortDu.at(r)>que) {
                    r--;
                }
                upper+=min(n-1-r,n-1-l);
            }
            int lower=0;
            for (auto &i:mp) {
                auto [u,v]=i.first;
                int cnt=i.second;
                if (du.at(u)+du.at(v)>que && du.at(u)+du.at(v)-cnt<=que) {
                    lower++;
                }
            }
            ans.at(i)=upper-lower;
        }
        return ans;
    }
};