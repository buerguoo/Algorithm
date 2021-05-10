#include<bits/stdc++.h>
using namespace std;
int n;
typedef pair<int,int> pii;
struct node{
    int pos,t,h,d;
};
bool cmp(node a,node b){
    return a.t<b.t;
}
bool cmp1(node a,node b){
    return a.pos<b.pos;
}
int cnt=0;
pii q[310000];
vector<node>v;
vector<int >ans;
int main(){
  cin>>n;
    for(int i=0;i<n;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        v.push_back(node{i,a,b,c});
    }
    sort(v.begin(),v.end(),cmp);
    ans.resize(n);
    for(int i=0;i<n;i++){
        int l=0,r=cnt;
        while(l<r){
            int mid=(l+r)/2;
            if(q[mid].first>=v[i].t-v[i].d){
                r=mid;
            }else l=mid+1;
        }
        ans[v[i].pos]+=(cnt-l);
        while(cnt>0&&q[cnt-1].second<=v[i].h)cnt--;
        q[cnt]={v[i].t,v[i].h};
        cnt++;
    }
    cnt=0;
    for(int i=n-1;i>=0;i--){
        int l=0,r=cnt;
        while(l<r){
            int mid=(l+r)/2;
            if(q[mid].first<=v[i].t+v[i].d){
                r=mid;
            }else l=mid+1;
        }
        ans[v[i].pos]+=(cnt-l);
        while(cnt>0&&q[cnt-1].second<=v[i].h)cnt--;
        q[cnt]={v[i].t,v[i].h};cnt++;
    }
    //sort(v.begin(),v.end(),cmp1);
    for(int i=0;i<n;i++){
        if(i)printf(" ");
        printf("%d",ans[i]);
    }
    return 0;
}