#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 100007
#define mid ((r+l)>>1)
#define lc (now<<1)
#define rc (now<<1|1)
using namespace std;
int n,m,mx[N<<2];
void build(int now,int l,int r)
{
    if(l==r)
        scanf("%d",&mx[now]);
    else
    {
        build(lc,l,mid);
        build(rc,mid+1,r);
        mx[now]=min(mx[lc],mx[rc]);
    }
}
int query(int now,int l,int r,int L,int R)
{
    if(L<=l && r<=R)
        return mx[now];
    int ans=0x3F3F3F3F;
    if(L<=mid)
        ans=min(ans,query(lc,l,mid,L,R));
    if(R>mid)
        ans=min(ans,query(rc,mid+1,r,L,R));
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    build(1,1,n);
    for(int i=1,x,y;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        printf("%d ",query(1,1,n,x,y));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}