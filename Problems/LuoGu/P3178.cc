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
int cnt,top,tot,n,m;
int val[N],fa[N],son[N],id[N],size[N],ct[N],deep[N];
struct edge_t{
    int dat;
    edge_t *nxt;
}e[N+(N<<1)];
struct node_t{
    long long sum,lazy;
    node_t *lc,*rc;
    inline void config(int l){
        if(!lazy)
            return;
        lc->lazy+=lazy;
        rc->lazy+=lazy;
        lc->sum+=(l-(l>>1))*lazy;
        rc->sum+=(l>>1)*lazy;
        lazy=0;
    }
    inline void refresh(){
        sum=lc->sum+rc->sum;
    }
}seg[N<<2],*root;
inline void add_edge(int x,int y){
    edge_t *now=&e[++tot];
    now->dat=y;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
}
void dfs_1(int x,int f,int d){
    deep[x]=d,fa[x]=f,size[x]=1;
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
    val[id[x]=++cnt]=e[x].dat;
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
node_t *build(int l,int r){
    node_t *now=&seg[++top];
    if(l==r)
        now->sum=val[l];
    else{
        now->lc=build(l,mid);
        now->rc=build(mid+1,r);
        now->refresh();
    }
    return now;
}
void update(node_t *now,int l,int r,int L,int R,long long v){
    if(L<=l && r<=R){
        now->lazy+=v;
        now->sum+=v*len;
        return;
    }
    now->config(len);
    if(L<=mid)
        update(now->lc,l,mid,L,R,v);
    if(R>mid)
        update(now->rc,mid+1,r,L,R,v);
    now->refresh();
}
long long query(node_t *now,int l,int r,int L,int R){
    if(L<=l && r<=R)
        return now->sum;
    long long ans=0;
    now->config(len);
    if(L<=mid)
        ans+=query(now->lc,l,mid,L,R);
    if(R>mid)
        ans+=query(now->rc,mid+1,r,L,R);
    now->refresh();
    return ans;
}
inline long long sum_query(int x,int y){
    long long ans=0;
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        ans+=query(root,1,n,id[ct[x]],id[x]);
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    return ans+query(root,1,n,id[x],id[y]);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    tot=n;
    for(int i=1;i<=n;++i)
        scanf("%d",&e[i].dat);
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(1,0,1);
    dfs_2(1,1);
    root=build(1,n);
    for(int i=1,c,x,y;i<=m;++i){
        scanf("%d%d",&c,&x);
        if(c==1){
            scanf("%d",&y);
            update(root,1,n,id[x],id[x],(long long)y);
        }
        else if(c==2){
            scanf("%d",&y);
            update(root,1,n,id[x],id[x]+size[x]-1,(long long)y);
        }
        else
            printf("%lld\n",sum_query(x,id[1]));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}