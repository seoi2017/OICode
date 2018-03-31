#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 300007
#define mid ((l+r)>>1)
#define len (r-l+1)
using namespace std;
int st[N],n,cnt,tot,top;
int ct[N],deep[N],size[N],id[N],fa[N],son[N];
struct edge_t{
    int dat;
    edge_t *nxt;
}e[N+(N<<1)];
inline void add_edge(int x,int y){
    edge_t *now=&e[++tot];
    now->dat=y;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
}
struct node_t{
    int sum,lazy;
    node_t *lc,*rc;
    inline void config(int l){
        if(!lazy)
            return;
        lc->lazy+=lazy;
        rc->lazy+=lazy;
        lc->sum+=lazy*(l-(l>>1));
        rc->sum+=lazy*(l>>1);
        lazy=0;
    }
    inline void refresh(){
        sum=lc->sum+rc->sum;
    }
}seg[N<<2],*root;
node_t *build(int l,int r){
    node_t *now=&seg[++top];
    now->sum=now->lazy=0;
    if(l!=r){
        now->lc=build(l,mid);
        now->rc=build(mid+1,r);
    }
    return now;
}
void update(node_t *now,int l,int r,int L,int R,int v){
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
int query(node_t *now,int pos,int l,int r){
    if(l==r)
        return now->sum;
    now->config(len);
    if(pos<=mid)
        return query(now->lc,pos,l,mid);
    else
        return query(now->rc,pos,mid+1,r);
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
inline void change(int x,int y){
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        update(root,1,n,id[ct[x]],id[x],1);
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    update(root,1,n,id[x],id[y],1);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&n);
    tot=n;
    for(int i=1;i<=n;++i)
        scanf("%d",&st[i]);
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(1,0,1);
    dfs_2(1,1);
    root=build(1,n);
    change(st[1],st[2]);
    for(int i=2;i<n;++i){
        change(st[i],st[i+1]);
        update(root,1,n,id[st[i]],id[st[i]],-1);
    }
    update(root,1,n,id[st[n]],id[st[n]],-1);
    for(int i=1;i<=n;++i)
        printf("%d\n",query(root,id[i],1,n));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}