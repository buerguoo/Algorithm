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
struct Node{
    int x;
    int y;
    bool operator < (const Node &r) const{
        return (double)x/y > (double)r.x/r.y;
    }
};
double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        priority_queue<Node> Q;
        int sz = classes.size();
        double res = 0;
        Node tmp;
        for(int i = 0;i < sz;++i){
            tmp.x = classes[i][0];
            tmp.y = classes[i][1];
            Q.push(tmp);
        }
        for(int i = 0;i < extraStudents;++i){
            tmp = Q.top();
            Q.pop();
            tmp.x += 1;
            tmp.y += 1;
            Q.push(tmp);
        }
        while(!Q.empty()){
            tmp = Q.top();
            Q.pop();
            res += (double)tmp.x/tmp.y;
        }
        return res/sz;
    }
int main()
{
    vector<vector<int>> classes = [[1,2],[3,5],[2,2]];
    
    return 0;
}