#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
#include <map>
#include <algorithm>
#include<stack>
using namespace std;
/*
    遍历两次数组，找到(使用栈)
    - 该数左边第一个比这个数小的数
    - 该数右边第一个比这个数小的数
    那么这个数就是这两个数所产生区间的最小值
*/

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int sz = nums.size();
        vector<int> left(sz, -1), right(sz, sz);
        stack<int> st;
        for(int i = 0;i < sz;++i){
            while(!st.empty() && nums[st.top()] > nums[i]){
                right[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        for(int i = sz-1;i >= 0;--i){
            while(!st.empty() && nums[st.top()] > nums[i]){
                left[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        int ans = 0;
        for(int i = 0;i < sz;++i){
            int l = left[i] + 1, r = right[i] - 1;
            if(l <= k && r >= k)
                ans = max(ans, (r-l+1)*nums[i]);
        }
        return ans;
    }
};