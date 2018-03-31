#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 500007
using namespace std;
int n,m,o;
int cnt;
int top;
int fa[N],son[N],size[N],deep[N],id[N],ct[N];
struct edge_t{
    int dat;
    edge_t *nxt;
}e[(N<<1)+N];
//Graph
inline void add_edge(int x,int y){
    edge_t *now=&e[++top];
    now->dat=y;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
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
inline int query(int x,int y){
    while(ct[x]!=ct[y]){
        if(deep[ct[x]]<deep[ct[y]])
            swap(x,y);
        x=fa[ct[x]];
    }
    if(deep[x]<deep[y])
        return x;
    return y;
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d%d",&n,&m,&o);
    top=n;
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(o,0,1);
    dfs_2(o,o);
    for(int i=1,x,y;i<=m;++i){
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}