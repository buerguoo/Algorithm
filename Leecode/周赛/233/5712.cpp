
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
    int getMaximumConsecutive(vector<int>& coins) {
        int x = 0;
        sort(coins.begin(), coins.end());
        int sz = coins.size();
        for(int i = 0;i < sz;++i)
            if(x + 1 >= coins[i])
                x += coins[i];
    }
};