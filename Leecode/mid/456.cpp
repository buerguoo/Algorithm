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
#include <stack>
using namespace std;
class Solution {
    const int INF = 1e9;
public:
    bool find132pattern(vector<int>& nums) {
        int sz = nums.size();
        int k = -INF;
        stack<int> s;
        for(int i = sz-1;i >= 0;--i){
            if(nums[i] < k) return true;
            while(!s.empty() && s.top() < nums[i]){
                if(k < s.top()) k = s.top();
                s.pop();
            }
            s.push(nums[i]);
        }
        return false;
    }
};