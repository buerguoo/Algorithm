#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdio>
#include <queue>
#include <fstream>
using namespace std;
//并查集
const int MAXN = 50010;
int F[MAXN], val[MAXN];

int find(int x)
{
    if(F[x] == -1)  return x;
    int tmp = find(F[x]);
    val[x] = (val[F[x]] + val[x]) % 3;
    return F[x] = tmp;
}

int main()
{
    int N, K;
    int sum;
    scanf("%d%d", &N, &K);
        memset(F, -1, sizeof(F));
        memset(val, 0, sizeof(val));
        sum = 0;
        while (K--)
        {
            int d, x, y;
            scanf("%d%d%d", &d, &x, &y);
            if(x > N || y > N)  sum++;
            else if(d == 2 && x == y)    sum++;
            else{
                int t1 = find(x);
                int t2 = find(y);
                if(t1 == t2){
                    if(d == 1 && val[x] != val[y])  sum++;
                    else if(d == 2 && ((3 - val[x] + val[y]) % 3 != d - 1))
                        sum++;
                }
                else{
                    F[t2] = t1;
                    val[t2] = (val[x]-val[y]+(d-1)+3)%3;
                }
            }
        }
        
        printf("%d\n", sum);    
    return 0;
}