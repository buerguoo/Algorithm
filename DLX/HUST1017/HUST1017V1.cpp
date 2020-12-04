# include <iostream>
#include <cstring>
using namespace std;
const int MAXN = 1000; //最大元素数量,稀疏矩阵
const int Head = 0; //头部元素
int Row[MAXN], Col[MAXN], Up[MAXN], Down[MAXN], 
Ans[MAXN], Right[MAXN], Left[MAXN], Len[MAXN]; //定义需要使用的数组
int CountNum = 0, nRows, nCols; //变量  

int Init(int Cols)
{
    //初始化Head的指向
    Up[Head] = Head, Down[Head] = Head;
    Left[Head] = Head, Right[Head] = Head;
    Col[Head] = 0, Row[Head] = 0;

    memset(Ans, 0, sizeof(Ans));

    //初始化标记元素C1...
    int col = 1;    //此时的列号
    for(CountNum = 1; CountNum <= Cols;CountNum++)
    {
        Up[CountNum] = CountNum, Down[CountNum] = CountNum;
        Left[CountNum] = CountNum-1, Right[CountNum-1] = CountNum;
        Right[CountNum] = Right[CountNum-1];
        Col[CountNum] = col++, Row[CountNum] = 0;
    }
    
    return 0;
}

int Add(int row, int col)
{
    //重新加入新的元素
    //需要注意的是，后加入元素后，需要同时更新与他相邻的上方和左方的元素的某些指针变量
    if(Row[CountNum-1] != row)
        Left[CountNum] = CountNum, Right[CountNum] = CountNum;
    else
        Left[CountNum] = CountNum-1, Right[CountNum] = Right[CountNum-1], Right[CountNum-1] = CountNum;
    Up[CountNum] = Up[col], Down[CountNum] = col;
    Down[Up[col]] = CountNum;
    Up[col] = CountNum;
    //printf("%d %d %d\n",Up[col], Down[col], col);
    Col[CountNum] = col, Row[CountNum] = row; 
    return 0;
}

int RemoveCol(int num)
{
    int col = Col[num];
    //消除该列的元素
    Right[Left[col]] = Right[col], Left[Right[col]] = Left[col];
    int row_ = num;
    do
    {
        int row = row_;
        printf("\t\trow_ = %d\n", row_);
        do
        {
            printf("row  = %d\n", row);
            Up[Down[row]] = Up[row], Down[Up[row]] = Down[row];
            row = Right[row];
        }while(row != row_);
        int temp = row_;
        row_ = Down[row_];
        if(!Row[row_])
            row_ = Down[row_];
        if(temp == row_)
            break;
    }while(row_ != Down[row_]);

    return 0;
}

int ResumeCol(int num)
{
    int col = Col[num];
    //消除该列的元素
    Right[Left[col]] = col, Left[Right[col]] = col;
    int row_ = num;
    do
    {
        int row = row_;
        printf("\t\trow_ = %d     %d\n", row_, Down[row_]);
        do
        {
            if(Row[row]){
            printf("RRR  = %d\n", row);
            Up[Down[row]] = row, Down[Up[row]] = row;
            row = Right[row];
            }
        }while(row != row_);
        row_ = Down[row_];
        //这是代码的问题所在，暂时没想到用好的方法解决
        if(!Row[row_])
            row_ = Up[Up[row_]];
    }while(row_ != num);

    return 0;
}

bool Dancing(int k)
{
    //如果头元素的右部等于其自身，判断成功
    if(Right[Head] == Head)
    {
        for(int i = 0;i < k;++i)
            printf("%d ", Ans[i]-nCols);
        printf("\n");

        return true;
    }
    int num =  Right[Head];
    do
    {
        printf("PPPnum = %d  num = %d\n",num, Down[num]);
        if(num == Down[num])
            break;
        num = Down[num];
        printf("num = %d\n",num);
        Ans[k] = num;
        //消除
        for(int i = 0;i < Len[Row[num]];++i)
        {
            RemoveCol(num);
            num = Right[num];
        }
        //递归调用
        if(Dancing(k + 1))
            return true;
        //回溯
        for(int i = 0;i < Len[Row[num]];++i)
        {
             ResumeCol(num);
             num = Right[num];
        }  
        //判断下一行
    }while(Row[num]);

    return false;
}

int main()
{
    cin >> nRows >> nCols;
    //对十字交叉循环双向链表进行初始化
    Init(nCols);
    int col;    //缓存当前输入元素的列号
    for(int row = 1;row <= nRows;row++)
    {
        cin >> Len[row];
        //使用数组来储存每一行的1的数量
        for(int j = 0;j < Len[row];++j)
        {
            cin >> col;
            //不断加入新的元素
            Add(row, col);
            CountNum++;
        }
    }

    if(!Dancing(0))
        printf("NO\n");

    return 0;
}