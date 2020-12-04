#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
#include<map>
#include<iomanip> 
#include<algorithm>
#include<vector>
#define INF 2e9
#define maxnode 5000
//别人的代码 人家过了...
using namespace std;

int empty[70];
long long square[200];//这个正方形需要哪些火柴 

struct DLX{
    int n,m,size;
    int up[maxnode],down[maxnode],R[maxnode],l[maxnode];
    int h[70],s[200],row[maxnode],col[maxnode];
    int ansd;
    
    void init(int n1,int m1){
        n=n1; m=m1;
        ansd=-1;
        for(int i=0;i<=m;i++){
            up[i] = down[i] = i;
            l[i] = i-1;
            R[i] = i+1;
            s[i]=0;
        }
        size=m;
        l[0]=m; R[m]=0;
        for(int i=1;i<=n;i++) h[i]=-1;
    }
    
    void link(int r,int c){
        row[ ++size ] = r; col[size]=c;
        s[c]++;
        up[size] = down[c];
        down[size]=c;
        down[up[c]]=size;
        up[c]=size;
        if( h[r]==-1 ) l[size]=R[size]=h[r]=size;
        else{
            l[size]=l[h[r]];
            R[size]=h[r];
            R[l[h[r]]]=size;
            l[h[r]]=size;
        }    
    }
    
    void remove(int c){
        for(int i=down[c];i!=c;i=down[i]){
            R[l[i]] = R[i];
            l[R[i]] = l[i];
        }
    }
    
    void resume(int c){
        for(int i=down[c];i!=c;i=down[i]){
            R[l[i]]=i;
            l[R[i]]=i;
        }
    }
    
    bool vis[200];
    int f(){
        int ret=0;
        for(int i=R[0];i!=0;i=R[i]) vis[i]=true;
        for(int i=R[0];i!=0;i=R[i]){
            if( vis[i] ){
                ret++;
                vis[i]=false;
                for(int j=down[i];j!=i;j=down[j]){
                    for(int k=R[j];k!=j;k=R[k]) vis[ col[k] ]=false;
                }
            }
        }
        return ret;
    }
    
    void dance(int d){
        if( ansd!=-1 && d>=ansd ) return;
        if( R[0]==0 ){
            ansd=d;
            return;
        }
        
        int c=R[0];
        for(int i=R[c];i!=0;i=R[i]){
            if( s[i]<s[c] ) c=i;
        }
        
        for(int i=down[c];i!=c;i=down[i]){
            remove(i);
            for(int j=R[i];j!=i;j=R[j]) remove(j);
            dance(d+1);
            for(int j=R[i];j!=i;j=R[j]) resume(j);
            resume(i);
        }    
        
    }
}dlx;


int main(){
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        memset(empty,0,sizeof(empty));
        int n,k1; cin>>n>>k1;
        for(int i=1;i<=k1;i++){
            int id; cin>>id;
            empty[id]=1;
        }
        
        int cnt=0;//有这么多个正方形 
        for(int i=1;i<=n;i++){//搜索长度为i的正方形 
            for(int j=0;j<=n-i;j++){
                for(int k=0;k<=n-i;k++){
                    //正方形的左上角在(j,k) 
                    //这样构造出来的正方形要哪些火柴
                    long long num=0;
                    bool configure=true;
                    
                    //上边
                    int id=k*(n+n+1)+j;
                    for(int j1=1;j1<=i;j1++){
                        id+=1;
                        if( empty[id] ) configure=false;
                        num+=  (long long)1<<id;
                    }
                    //左边
                    id=k*(n+n+1)+j-n;
                    for(int k1=1;k1<=i;k1++){
                        id+=(n+n+1);
                        if( empty[id] ) configure=false;
                        num+= (long long)1<<id;
                    } 
                    //下边
                    id=(k+i)*(n+n+1)+j;
                    for(int j1=1;j1<=i;j1++){
                        id++;
                        if( empty[id] ) configure=false;
                        num+=  (long long)1<<id;
                    }
                    //右边
                    id=k*(n+n+1)+j+i-n;
                    for(int k1=1;k1<=i;k1++){
                        id+=n+n+1;
                        if( empty[id] ) configure=false;
                        num+= (long long)1<<id;
                    }
                    
                    if( configure ) square[++cnt]=num;
                }
            }
        }
        
        dlx.init(2*n*(n+1),cnt);
        for(int i=1;i<=2*n*(n+1);i++){
            for(int j=1;j<=cnt;j++){
                if( ((long long)1<<i)&square[j] ) dlx.link(i,j);
            }    
        }

        dlx.dance(0);
        cout<<dlx.ansd<<endl;    
    }
    

    return 0;    
}