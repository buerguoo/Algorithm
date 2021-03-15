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
class Solution {
public:
    int findCenter(vector<vector<int>>& edges) {
        int res = 0;
        for(int i = 0;i < 2;++i){
            for(int j = 0;j < 2;++j)
                if(edges[0][i] == edges[1][j]) res = edges[0][i];
        }
        return res;
    }
};