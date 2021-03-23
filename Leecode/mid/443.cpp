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
const int INF = 0x3f3f3f3f;
const int MAXN = 10010;
const int MAXM = 100010;
class Solution {
public:
    int compress(vector<char>& chars) {
        int count = 1;
        int sz = chars.size();
        vector<char> res;
        stack<char> S;
        for(int i = 1;i < sz;++i){
            if(chars[i] == chars[i-1])  count++;
            else{
                res.push_back(chars[i-1]);
                if(count > 1){
                    while(count){
                        int t1 = count % 10;
                        count /= 10;
                        S.push(t1+'0');
                    }
                    while(!S.empty()){
                        char c = S.top();
                        S.pop();
                        res.push_back(c);
                    }
                } 
                count = 1;
            }if(i == sz-1){
                res.push_back(chars[i-1]);
                if(count > 1){
                    while(count){
                        int t1 = count % 10;
                        count /= 10;
                        S.push(t1+'0');
                    }
                    while(!S.empty()){
                        char c = S.top();
                        S.pop();
                        res.push_back(c);
                    }
                } 
                count = 1;
            }
        }
        if(sz != 1) chars = res;
        return chars.size();
    }
};