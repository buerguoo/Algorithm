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
#define FILL(a, b)  memset(a, b, sizeof(a))
#define lson l, m, rt<<1
#define rson m+1, r, rt<<1|1
#define ls(i) i<<1
#define rs(i) i<<1|1
typedef long long ll;
const int MAXN = 2005;
struct Node{
    int l, r, ll, lr;
    int sum1, sum2, summ, cover;
}T[MAXN];
struct 
