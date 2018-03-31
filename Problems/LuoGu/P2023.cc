#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 200007
#define mid ((l+r)>>1)
#define len (r-l+1)
#define lc (now<<1)
#define rc (now<<1|1)
#define lsize (l-(l>>1))
#define rsize (l>>1)
using namespace std;
int n,m,P;
int sum[N<<2],add[N<<2],mul[N<<2];
inline void config(int now,int l)
{ //标记下传
    if(mul[now]==1 && add[now]==0)
        return;
    mul[lc]=(long long)mul[lc]*mul[now]%P;
    mul[rc]=(long long)mul[rc]*mul[now]%P;
    add[lc]=((long long)add[lc]*mul[now]+add[now])%P;
    add[rc]=((long long)add[rc]*mul[now]+add[now])%P;
    sum[lc]=((long long)sum[lc]*mul[now]+(long long)add[now]*lsize)%P;
    sum[rc]=((long long)sum[rc]*mul[now]+(long long)add[now]*rsize)%P;
    mul[now]=1,add[now]=0;
}
inline void refresh(int now)
{ //节点更新
    sum[now]=(sum[lc]+sum[rc])%P;
}
void build(int now,int l,int r)
{ //建树
    mul[now]=1,add[now]=0;
    if(l==r)
        scanf("%d",&sum[now]);
    else
    {
        build(lc,l,mid);
        build(rc,mid+1,r);
        refresh(now);
    }
}
void add_update(int now,int l,int r,int L,int R,int v)
{ //加法更新
    if(L<=l && r<=R)
    {
        add[now]=(add[now]+v)%P;
        sum[now]=((long long)sum[now]+v*len)%P;
        return;
    }
    config(now,len);
    if(L<=mid)
        add_update(lc,l,mid,L,R,v);
    if(R>mid)
        add_update(rc,mid+1,r,L,R,v);
    refresh(now);
}
void mul_update(int now,int l,int r,int L,int R,int v)
{ //乘法更新
    if(L<=l && r<=R)
    {
        add[now]=((long long)add[now]*v)%P;
        sum[now]=((long long)sum[now]*v)%P;
        mul[now]=((long long)mul[now]*v)%P;
        return;
    }
    config(now,len);
    if(L<=mid)
        mul_update(lc,l,mid,L,R,v);
    if(R>mid)
        mul_update(rc,mid+1,r,L,R,v);
    refresh(now);
}
int query(int now,int l,int r,int L,int R)
{ //查询
    if(L<=l && r<=R)
        return sum[now];
    int ans=0;
    config(now,len);
    if(L<=mid)
        ans=(ans+query(lc,l,mid,L,R))%P;
    if(R>mid)
        ans=(ans+query(rc,mid+1,r,L,R))%P;
    refresh(now);
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&P);
    build(1,1,n);
    scanf("%d",&m);
    for(int i=1,c,x,y,z;i<=m;++i)
    {
        scanf("%d%d%d",&c,&x,&y);
        if(c==3)
            printf("%d\n",query(1,1,n,x,y));
        else
        {
            scanf("%d",&z);
            if(c==1)
                mul_update(1,1,n,x,y,z);
            else
                add_update(1,1,n,x,y,z);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}