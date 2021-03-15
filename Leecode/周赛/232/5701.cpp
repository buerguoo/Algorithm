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
    int count = 0, x[100], sz = 0;
public:
    bool areAlmostEqual(string s1, string s2) {
        if(s1.length() != s2.length()) return false;
        sz = s1.length();
        for(int i = 0;i < sz;++i)
            if(s1[i] != s2[i]){
                x[count++] = i;
            }
        if(!count) return true;
        if(count != 2) return false;
        if(s1[x[0]] == s2[x[1]] && s1[x[1]] == s2[x[0]]) return true;

        return false;
    }
};