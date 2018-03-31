#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 300005
#define EPS 600007
#define mid ((l+r)>>1)
namespace var{
    using namespace std;
    int n,m,top,wt[N];
    struct edge_t{
        int dat;
        edge_t *nxt;
    }e[N+(N<<1)];
    struct question_t{
        int st,et,lca;
    }q[N];
    inline void add_edge(int x,int y){
        edge_t *now=&e[++top];
        now->dat=y;
        now->nxt=e[x].nxt;
        e[x].nxt=now;
    }
}
namespace tree{
    //动态开点的线段树
    int root[N<<2],lc[N<<6],rc[N<<6],sum[N<<6],tot=0;
    void update(int &now,int l,int r,int pos,int v){
        //引用的意义是动态开点时直接更新父节点的对应子节点信息
        if(!pos)//根节点的父节点为0,这里排除
            return;
        if(!now)
            now=++tot;
        sum[now]+=v;
        if(l==r)
            return;
        if(pos<=mid)
            update(lc[now],l,mid,pos,v);
        else
            update(rc[now],mid+1,r,pos,v);
    }
    int query(int now,int l,int r,int L,int R){
        if(L<=l && r<=R)
            return sum[now];
        int ans=0;
        if(L<=mid)
            ans+=query(lc[now],l,mid,L,R);
        if(R>mid)
            ans+=query(rc[now],mid+1,r,L,R);
        return ans;
    }
}
namespace chain{
    using namespace var;
    int deep[N],ct[N],fa[N],son[N],size[N],id[N],in[N],out[N],cnt;
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
        ct[x]=chain_top;
        in[x]=(id[x]=++cnt);
        if(!son[x]){
            out[x]=cnt;
            return;
        }
        dfs_2(son[x],chain_top);
        for(edge_t *k=e[x].nxt;k;k=k->nxt){
            int y=k->dat;
            if(y==fa[x] || y==son[x])
                continue;
            dfs_2(y,y);
        }
        out[x]=cnt;
    }
    int lca(int x,int y){
        while(ct[x]!=ct[y]){
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            x=fa[ct[x]];
        }
        return deep[x]<deep[y]?x:y;
    }
}
namespace solve{
    using namespace chain;
    using namespace tree;
    int ans[N];
    inline void clear(){
        memset(root,0,sizeof(root));
        memset(lc,0,sizeof(lc));
        memset(rc,0,sizeof(rc));
        memset(sum,0,sizeof(sum));
        tot=0;
    }
    inline void work(){
        for(int i=1;i<=m;++i){
            update(root[deep[q[i].st]],1,n,id[q[i].st],1);
            update(root[deep[q[i].st]],1,n,id[fa[q[i].lca]],-1);
        }
        for(int i=1;i<=n;++i)//上行答案统计
            ans[i]+=query(root[deep[i]+wt[i]],1,n,in[i],out[i]);
        clear();
        for(int i=1;i<=m;++i){
            update(root[2*deep[q[i].lca]-deep[q[i].st]+EPS],1,n,id[q[i].et],1);
            update(root[2*deep[q[i].lca]-deep[q[i].st]+EPS],1,n,id[q[i].lca],-1);
        }
        for(int i=1;i<=n;++i)//下行答案统计
            ans[i]+=query(root[deep[i]-wt[i]+EPS],1,n,in[i],out[i]);
        for(int i=1;i<=n;++i)
            printf("%d ",ans[i]);
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    using namespace solve;
    scanf("%d%d",&n,&m);
    top=n;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(1,0,1);
    dfs_2(1,1);
    for(int i=1;i<=n;++i)
        scanf("%d",&wt[i]);
    for(int i=1;i<=m;++i){
        scanf("%d%d",&q[i].st,&q[i].et);
        q[i].lca=lca(q[i].st,q[i].et);
    }
    work();
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}