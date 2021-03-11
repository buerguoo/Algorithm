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
bool scan_d(int &res)
{
    char c;
    if(c = getchar(), c == EOF) return 0;
    if(c < '0' || c > '9'){
        while(c = getchar() && c != EOF);
        res = -1;
        return 0;
    } 
    res = 0;
    while(c = getchar(), c >= '0' && c <= '9')  res = res*10+(c-'0');
    if(res < 0 || res > 8) return 0;
    return 1;
}
int main()
{   
    int a;
    scan_d(a);
    printf("%d\n", a);
    return 0;
}