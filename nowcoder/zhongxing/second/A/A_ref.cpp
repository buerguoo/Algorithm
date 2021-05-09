#include<iostream>
using namespace std;
long long k,a,b;
int main(void){
    cin>>k>>a>>b;
    int ans=-1;
    if(k>0 && k<=a) ans=1;
    else if(k*(a-b)<=0) ans=-1;
    else{
        if(k>0) ans=(k-a)/(a-b)+1+((k-a)%(a-b)==0?0:1);
        else ans=k/(a-b)+(k%(a-b)==0?0:1);
    }
    cout<<ans<<endl;
}