#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 100007
#define mid ((l+r)>>1)
#define len (r-l+1)
using namespace std;
int n,m,top;
struct edge_t{
    int dat;
    edge_t *nxt;
}e[N+(N<<1)];
inline void add_edge(int x,int y){
    edge_t *now=&e[++top];
    now->dat=y;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
}
namespace tree{
    int lazy[N<<2],sum[N<<2];
    inline void config(int now,int l){
        if(!lazy[now])
            return;
        lazy[now<<1]+=lazy[now];
        lazy[now<<1|1]+=lazy[now];
        sum[now<<1]+=lazy[now]*(l-(l>>1));
        sum[now<<1|1]+=lazy[now]*(l>>1);
        lazy[now]=0;
    }
    inline void refresh(int now){
        sum[now]=sum[now<<1]+sum[now<<1|1];
    }
    void update(int now,int l,int r,int L,int R,int v){
        if(L<=l && r<=R){
            lazy[now]+=v;
            sum[now]+=v*len;
            return;
        }
        config(now,len);
        if(L<=mid)
            update(now<<1,l,mid,L,R,v);
        if(R>mid)
            update(now<<1|1,mid+1,r,L,R,v);
        refresh(now);
    }
    int query(int now,int pos,int l,int r){
        if(l==r)
            return sum[now];
        config(now,len);
        if(pos<=mid)
            return query(now<<1,pos,l,mid);
        else
            return query(now<<1|1,pos,mid+1,r);
        refresh(now);
    }
}
namespace chain{
    int deep[N],size[N],fa[N],son[N],ct[N],id[N],cnt=0;
    void dfs_1(int x,int f,int d){
        deep[x]=d,size[x]=1,fa[x]=f;
        int maxson=-1,y;
        for(edge_t *k=e[x].nxt;k;k=k->nxt){
            y=k->dat;
            if(y==f)
                continue;
            dfs_1(y,x,d+1);
            size[x]+=size[y];
            if(size[y]>maxson)
                son[x]=y,maxson=size[y];
        }
    }
    void dfs_2(int x,int chain_top){
        id[x]=++cnt;
        ct[x]=chain_top;
        if(!son[x])
            return;
        dfs_2(son[x],chain_top);
        for(edge_t *k=e[x].nxt;k;k=k->nxt){
            int y=k->dat;
            if(y==fa[x] || y==son[x])
                continue;
            dfs_2(y,y);
        }
    }
    void update(int x,int y){
        while(ct[x]!=ct[y]){
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            tree::update(1,1,n,id[ct[x]],id[x],1);
            x=fa[ct[x]];
        }
        if(deep[x]>deep[y])
            swap(x,y);
        tree::update(1,1,n,id[x],id[y],1);
        tree::update(1,1,n,id[x],id[x],-1);
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    top=n;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d\n",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    chain::dfs_1(1,0,1);
    chain::dfs_2(1,1);
    for(int i=1,x,y;i<=m;++i){
        char c;
        scanf("%c%d%d\n",&c,&x,&y);
        if(c=='P')
            chain::update(x,y);
        else
            printf("%d\n",tree::query(1,chain::deep[x]<chain::deep[y]?chain::id[y]:chain::id[x],1,n));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}