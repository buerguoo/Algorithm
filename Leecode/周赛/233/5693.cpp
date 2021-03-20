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
    int num[10], count = 0, tmp[10], k;
public:
    int secondHighest(string s) {
        int lh = s.length();
        memset(num, 0, sizeof(num));
        for(int i = 0;i < lh;++i){
            if(s[i] >= '0' && s[i] <= '9')
                num[s[i]-'0']++;
        }
        for(int i = 0;i < 10;++i)
            if(num[i] != 0) {
                tmp[count++] = i;
                
            }   
        if(count < 2) return -1;
        else return tmp[count-2];
    }
};