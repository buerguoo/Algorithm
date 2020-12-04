#include <iostream>
#include <cstring>
#include <map>
#include <queue>
using namespace std;

const char ans[36] = {
    11, 12, 13, 14, 15, 16, 17, 1,
    21, 22, 23, 24, 25, 26, 27, 1,
    31, 32, 33, 34, 35, 36, 37, 1,
    41, 42, 43, 44, 45, 46, 47, 1
};
struct Node
{
    string map;
    int ind[4];
    int step;
};
char st[36];
int tp[4];
int bfs()
{
    queue<Node> Q;
    map<string,int> P;
    Node N1,N2;
    memcpy(N1.ind,tp,sizeof(tp));
    N1.map = st;
    N1.step = 0;
    Q.push(N1);
    while(!Q.empty())
    {
        N2 = Q.front();
        Q.pop();
        for(int i = 0;i < 4;++i)
        {
            int t = N2.ind[i] - 1;
            for(int j = 0;j < 36;++j)
            {
                if(N2.map[j] == N2.map[t] + 1)
                {
                    N2.map[t+1] = N2.map[j];
                    N2.map[j] = 1;
                    break;
                }
            }

            N2.step++;
            if(strcmp(N2.map.c_str(),ans) == 0)
                return N2.step;
            if(!P[N2.map])
            {
                P[N2.map] == 1;
                Q.push(N2);
            }
        }
    }
    return -1;
}

int main()
{
    int t,k,p;
    scanf("%d",&t);
    while(t--)
    {   
        k = 0,p = 0;
        for(int i = 0;i < 4;++i)
        {
            st[k++] = i*10+1;
            for(int j = 1;j <= 7;++j){
                int temp;
                scanf("%d",&temp);
                st[k] = temp;
                if(temp%10 == 1)
                {
                    tp[p++] = temp;
                    st[k] = 1;
                }
                k++;
            }
        }
        printf("%d\n",bfs());

    }
    return 0;
}