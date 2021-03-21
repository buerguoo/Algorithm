/*
Author:buerguoo
Time:
memory:

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
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 100010;
class Solution {
public:
    int tmp, tp = 0;
    priority_queue<int> Q;
    int maxAscendingSum(vector<int>& nums) {
        int sz = nums.size();
        tmp = nums[0];
        for(int i = 1;i < sz;++i){
            if(nums[i] > nums[i-1]){
                tmp += nums[i];
            }else{
                Q.push(tmp);
                tmp = nums[i];
            }
        }
        Q.push(tmp);
        return Q.top();
    }
};