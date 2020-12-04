#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 通过递归实现深度有限搜索

char code[8][8];                    //字符串数组记录输入的棋盘
int n,k;                              //输入的棋盘大小n与摆放棋盘的个数k
int step[10];                       //记录每列是否填入棋盘
int num;                        //记录可能的个数

void dfs(int co,int row)
{
    int i;
    if(co == k){
        num++;
        return;
    }
    if(row >= n) return;
    for(i = 0;i < n;i++){
        if(code[row][i] == '#' && step[i] == 0)
        {
            step[i] = 1;
            dfs(co+1,row+1);
            step[i] = 0;
        }
    }
    dfs(co,row+1);
}

int main()
{
    int i;
    while(1){
    scanf("%d %d",&n,&k);
    if(n==-1&&k==-1)  return 0;
    for(i = 0;i < n;i++)
        scanf("%s",code[i]);
    memset(step,0,sizeof(step));
    num = 0;
    dfs(0,0);
    printf("%d\n",num);
}
    return 0;
}



