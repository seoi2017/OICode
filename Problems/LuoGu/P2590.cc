#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 30007
#define S 8
#define mid ((l+r)>>1)
#define len (r-l+1)
using namespace std;
char com[S];
int n,q,cnt,top,tot;
int val[N],son[N],size[N],ct[N],id[N],deep[N],fa[N];
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
    long long max,sum;
    node_t *lc,*rc;
    inline void refresh(){
        this->sum=lc->sum+rc->sum;
        this->max=std::max(lc->max,rc->max);
    }
}seg[N<<2],*root;
node_t *build(int l,int r){
    node_t *now=&seg[++top];
    if(l==r)
        now->sum=now->max=val[l];
    else{
        now->lc=build(l,mid);
        now->rc=build(mid+1,r);
        now->refresh();
    }
    return now;
}
void update(node_t *now,int l,int r,int pos,long long num){
    if(l==r){
        now->sum=now->max=num;
        return;
    }
    if(pos<=mid)
        update(now->lc,l,mid,pos,num);
    else
        update(now->rc,mid+1,r,pos,num);
    now->refresh();
}
long long sum_query(node_t *now,int l,int r,int L,int R){
    if(L<=l && r<=R)
        return now->sum;
    long long ans=0;
    if(L<=mid)
        ans+=sum_query(now->lc,l,mid,L,R);
    if(R>mid)
        ans+=sum_query(now->rc,mid+1,r,L,R);
    return ans;
}
long long max_query(node_t *now,int l,int r,int L,int R){
    if(L<=l && r<=R)
        return now->max;
    long long ans=-1e9;
    if(L<=mid)
        ans=max(ans,max_query(now->lc,l,mid,L,R));
    if(R>mid)
        ans=max(ans,max_query(now->rc,mid+1,r,L,R));
    return ans;
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
inline long long max_Q(int x,int y){
    long long ans=-1e9;
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        ans=max(ans,max_query(root,1,n,id[ct[x]],id[x]));
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    return max(ans,max_query(root,1,n,id[x],id[y]));
}
inline long long sum_Q(int x,int y){
    long long ans=0;
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        ans+=sum_query(root,1,n,id[ct[x]],id[x]);
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    return ans+sum_query(root,1,n,id[x],id[y]);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&n);
    tot=n;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    for(int i=1;i<=n;++i)
        scanf("%d",&e[i].dat);
    dfs_1(1,0,1);
    dfs_2(1,1);
    root=build(1,n);
    scanf("%d",&q);
    for(int i=1,u,v;i<=q;++i){
        scanf("%s%d%d",com,&u,&v);
        if(com[0]=='C')
            update(root,1,n,id[u],(long long)v);
        else if(com[1]=='M')
            printf("%lld\n",max_Q(u,v));
        else
            printf("%lld\n",sum_Q(u,v));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}