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
typedef long long ll;
ll sum(int len, int num){
    if(num > len)  return (num+num-len+1)*len/2;
    else return (num+1)*num/2 + (len-num);
}
class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        int left = index, right = n - index - 1;
        int low = 1, high = maxSum-n+1; 
        while(low <= high){
            int mid = (low+high)/2;
            int t1 = sum(left, mid-1);
            int t2 = sum(right, mid-1);
            if(t1 + t2 + mid > maxSum) high = mid - 1;
            else low = mid + 1;
        }
        return high;
    }
};