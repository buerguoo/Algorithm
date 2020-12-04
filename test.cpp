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
typedef long long ll;

const int maxn=1010;
const int maxz=510;

int n;

vector<int> x;
inline int getidx(int val){return lower_bound(x.begin(),x.end(),val)-x.begin();}

vector<int> z;

int tot;
struct Segment
{
    int x1,x2,y;
    int z1,z2;
    int flag;
    bool operator <(const Segment &oth)const{
        return y<oth.y;
    }
}segment[2*maxn],tmp[2*maxn];

/********************************* Segment Tree - st *********************************/
struct Node{
    int l,r;
    int s;
    int once,twice,more;
    void show()
    {
        printf("l=%d r=%d s=%d once=%d twice=%d more=%d\n",l,r,s,once,twice,more);
    }
}node[8*maxn];
void pushup(int rt)
{
    int ls=rt*2,rs=rt*2+1;
    if(node[rt].s>2)
    {
        node[rt].more=x[node[rt].r+1]-x[node[rt].l];
        node[rt].once=node[rt].twice=0;
    }
    else if(node[rt].s==2)
    {
        if(node[rt].l==node[rt].r)
        {
            node[rt].more=0;
            node[rt].twice=x[node[rt].r+1]-x[node[rt].l];
            node[rt].once=0;
        }
        else
        {
            node[rt].more=node[ls].once+node[ls].twice+node[ls].more+node[rs].once+node[rs].twice+node[rs].more;
            node[rt].twice=x[node[rt].r+1]-x[node[rt].l]-node[rt].more;
            node[rt].once=0;
        }
    }
    else if(node[rt].s==1)
    {
        if(node[rt].l==node[rt].r)
        {
            node[rt].more=0;
            node[rt].twice=0;
            node[rt].once=x[node[rt].r+1]-x[node[rt].l];
        }
        else
        {
            node[rt].more=node[ls].twice+node[ls].more+node[rs].twice+node[rs].more;
            node[rt].twice=node[ls].once+node[rs].once;
            node[rt].once=x[node[rt].r+1]-x[node[rt].l]-node[rt].more-node[rt].twice;
        }
    }
    else
    {
        if(node[rt].l==node[rt].r)
        {
            node[rt].more=0;
            node[rt].twice=0;
            node[rt].once=0;
        }
        else
        {
            node[rt].more=node[ls].more+node[rs].more;
            node[rt].twice=node[ls].twice+node[rs].twice;
            node[rt].once=node[ls].once+node[rs].once;
        }
    }
    //printf("now pushup rt=%d\t",rt); node[rt].show();
}
void build(int rt,int l,int r)
{
    if(l>r) return;
    node[rt].l=l; node[rt].r=r;
    node[rt].s=0;
    node[rt].once=node[rt].twice=node[rt].more=0;
    if(l==r) return;
    else
    {
        int mid=l+(r-l)/2;
        build(rt*2,l,mid);
        build(rt*2+1,mid+1,r);
        pushup(rt);
    }
}
void update(int root,int st,int ed,int val)
{
    if(st>node[root].r || ed<node[root].l) return;
    if(st<=node[root].l && node[root].r<=ed)
    {
        node[root].s+=val;
        pushup(root);
    }
    else
    {
        update(root*2,st,ed,val);
        update(root*2+1,st,ed,val);
        pushup(root);
    }
}
/********************************* Segment Tree - st *********************************/

int main()
{
    int T;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d",&n);

        x.clear();
        z.clear();
        tot=0;
        for(int i=1;i<=n;i++)
        {
            int x1,y1,z1,x2,y2,z2;
            scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);

            segment[tot].x1=x1; segment[tot].x2=x2; segment[tot].y=y1;
            segment[tot].z1=z1; segment[tot].z2=z2;
            segment[tot].flag=1;
            tot++;

            segment[tot].x1=x1; segment[tot].x2=x2; segment[tot].y=y2;
            segment[tot].z1=z1; segment[tot].z2=z2;
            segment[tot].flag=-1;
            tot++;

            x.push_back(x1);
            x.push_back(x2);
            z.push_back(z1);
            z.push_back(z2);
        }

        sort(x.begin(),x.end());
        x.erase(unique(x.begin(),x.end()),x.end());

        sort(z.begin(),z.end());
        z.erase(unique(z.begin(),z.end()),z.end());

        ll ans=0;
        for(int i=0;i<z.size()-1;i++)
        {
            //printf("now z=%d\n",z[i]);
            int cnt=0;
            for(int j=0;j<tot;j++) if(segment[j].z1<=z[i] && segment[j].z2>z[i]) tmp[cnt++]=segment[j];
            sort(tmp,tmp+cnt);

            build(1,0,x.size());
            ll area=0;
            for(int j=0;j<cnt-1;j++)
            {
                int l=getidx(tmp[j].x1);
                int r=getidx(tmp[j].x2);
                //printf("now update y=%d [%d,%d](%d,%d) += %d\n",tmp[j].y,x[l],x[r],l,r-1,tmp[j].flag);
                update(1,l,r-1,tmp[j].flag);
                area+=(ll)node[1].more*(tmp[j+1].y-tmp[j].y);
            }
            ans+=area*(z[i+1]-z[i]);
        }

        printf("Case %d: %I64d\n",kase,ans);
    }
}