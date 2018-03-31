#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 100007
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
namespace chain{
    int deep[N],size[N],fa[N],son[N],ct[N];
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
    int lca(int x,int y){
        while(ct[x]!=ct[y]){
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            x=fa[ct[x]];
        }
        return deep[x]<deep[y]?x:y;
    }
}
int tc[N],lca[N],ans=-1;
void solve(int x){
    for(edge_t *k=e[x].nxt;k;k=k->nxt)
        if(k->dat!=chain::fa[x]){
            solve(k->dat);
            tc[x]+=tc[k->dat];
        }
    ans=max(ans,tc[x]);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    top=n;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    chain::dfs_1(1,0,1);
    chain::dfs_2(1,1);
    for(int i=1,x,y;i<=m;++i){
        scanf("%d%d",&x,&y);
        ++tc[x],++tc[y];
        lca[i]=chain::lca(x,y);
        --tc[lca[i]];
        --tc[chain::fa[lca[i]]];
    }
    solve(1);
    printf("%d\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}