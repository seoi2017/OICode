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
int n,m,o,p;
int cnt;
int top,tot;
int fa[N],son[N],size[N],deep[N],val[N],id[N],ct[N];
struct edge_t{
    int dat;
    edge_t *nxt;
}e[(N<<1)+N];
struct node_t{
    int sum,lazy;
    node_t *lc,*rc;
    inline void config(int l){
        if(this->lazy==0)
            return;
        lc->lazy+=this->lazy;
        rc->lazy+=this->lazy;
        lc->sum=(lc->sum+this->lazy*(l-(l>>1)))%p;
        rc->sum=(rc->sum+this->lazy*(l>>1))%p;
        this->lazy=0;
    }
    inline void refresh(){
        sum=(lc->sum+rc->sum)%p;
    }
}seg[N<<2],*root;
//Graph
inline void add_edge(int x,int y){
    edge_t *now=&e[++top];
    now->dat=y;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
}
//Segment Tree
node_t *build(int l,int r){
    node_t *now=&seg[++tot];
    if(l==r){
        now->sum=val[l]%p;
        return now;
    }
    now->lc=build(l,mid);
    now->rc=build(mid+1,r);
    now->refresh();
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
int query(node_t *now,int l,int r,int L,int R){
    if(L<=l && r<=R)
        return now->sum;
    int ans=0;
    now->config(len);
    if(L<=mid)
        ans=(ans+query(now->lc,l,mid,L,R))%p;
    if(R>mid)
        ans=(ans+query(now->rc,mid+1,r,L,R))%p;
    return ans;
}
//Tree Chain Subdivision
void dfs_1(int x,int f,int d){
    deep[x]=d,fa[x]=f;
    size[x]=1;
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
inline void range_update(int x,int y,int v){
    v%=p;
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        update(root,1,n,id[ct[x]],id[x],v);
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    update(root,1,n,id[x],id[y],v);
}
inline int range_query(int x,int y){
    int ans=0;
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        ans=(ans+query(root,1,n,id[ct[x]],id[x]))%p;
        x=fa[ct[x]];
    }
    if(deep[x]>deep[y])
        swap(x,y);
    ans=(ans+query(root,1,n,id[x],id[y]))%p;
    return ans;
}
inline void subtree_update(int x,int v){
    update(root,1,n,id[x],id[x]+size[x]-1,v);
}
inline int subtree_query(int x){
    return query(root,1,n,id[x],id[x]+size[x]-1);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d%d%d",&n,&m,&o,&p);
    top=n;
    for(int i=1;i<=n;++i)
        scanf("%d",&e[i].dat);
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(o,0,1);
    dfs_2(o,o);
    root=build(1,n);
    for(int i=1,c,x,y,z;i<=m;++i){
        scanf("%d%d",&c,&x);
        switch(c){
            case 1:
                scanf("%d%d",&y,&z);
                range_update(x,y,z);
                break;
            case 2:
                scanf("%d",&y);
                printf("%d\n",range_query(x,y));
                break;
            case 3:
                scanf("%d",&z);
                subtree_update(x,z);
                break;
            case 4:
                printf("%d\n",subtree_query(x));
                break;
            default:break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}