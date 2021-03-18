/*
Author:buerguoo
Time:
memory:

Data:
*/
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
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n);
        for(int i = 0;i < n;++i)
            matrix[i].resize(n);
        int l = 0, u = 0;
        int d = n - 1, r = n - 1;
        int num = 1;
        while(true){
            for(int i = l;i <= r;i++) matrix[u][i] = num++;
            if(u++ >= d) break;
            for(int i = u;i <= d;++i) matrix[i][r] = num++;
            if(r-- <= l) break;
            for(int i = r;i >= l;--i) matrix[d][i] = num++;
            if(d++ <= u) break;
            for(int i = d;i >= u;--i) matrix[i][l] = num++;
            if(l++ >= r) break; 
        } 
        return matrix;
    }
};