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
struct buy{
    int price;
    int count;
    bool operator< (const buy &r) const{
        return price<r.price;
    }
};
struct sell
{
    int price;
    int count;
    bool operator< (const sell &r) const{
        return price>r.price;
    }
};

class Solution {
public:
    priority_queue<buy> Buy;
    priority_queue<sell> Sell;
    const int MOD = 1e9+7;
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        int sz = orders.size();
        for(int i = 0;i < sz;++i){
            if(orders[i][2] == 1){
                while(!Buy.empty() && Buy.top().price >= orders[i][0] && orders[i][1] >= 0){
                    buy tmp = Buy.top();
                    Buy.pop();
                    tmp.count -= orders[i][1];
                    if(tmp.count <= 0){
                        orders[i][1] -= Buy.top().count; 
                    }else{
                        Buy.push(tmp);
                        orders[i][1] = 0;
                    } 
                }if(orders[i][1] != 0){
                    sell s;
                    s.price = orders[i][0];
                    s.count = orders[i][1];
                    Sell.push(s);
                }
            }else{
                while(!Sell.empty() && Sell.top().price <= orders[i][0] && orders[i][1] >= 0){
                    sell tmp = Sell.top();
                    Sell.pop();
                    tmp.count -= orders[i][1];
                    if(tmp.count <= 0){
                        orders[i][1] -= Sell.top().count; 
                    }else{
                        Sell.push(tmp);
                        orders[i][1] = 0;
                    } 
                }if(orders[i][1] != 0){
                    buy s;
                    s.price = orders[i][0];
                    s.count = orders[i][1];
                    Buy.push(s);
                }
        }
    }
    long long res = 0;
    while(!Buy.empty()){
        buy tmp = Buy.top();
        res += tmp.count;
        Buy.pop();
    }
    while(!Sell.empty()){
        sell tmp = Sell.top();
        Sell.pop();
        res += tmp.count;
    }
    return res%MOD;
}
};   