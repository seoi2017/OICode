#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#define N 100003
#define M 1000007
#define INF 0x3F3F3F3F
using namespace std;
typedef long long ll_t;
struct edge_t{
    int dat,len;
    bool block;
    edge_t *nxt;
}p[M+N],*mine;
int n,m,k,top;
bool escape[N],vis[N];
ll_t dis[N],ans=(((ll_t)INF<<32)|INF);
inline void add_edge(int x,int y,int z){
    p[++top].dat=y,p[top].len=z,p[top].block=false;
    p[top].nxt=p[x].nxt,p[x].nxt=&p[top];
}
void dfs(int x){
    vis[x]=true,mine=NULL;
    int mne=INF;
    for(edge_t *k=p[x].nxt;k!=NULL;k=k->nxt)
        if(k->len<mne)
            mne=k->len,mine=k;
    if(p[x].nxt!=NULL)
        mine->block=true;
    for(edge_t *k=p[x].nxt;k!=NULL;k=k->nxt)
        if(!vis[k->dat])
            dfs(k->dat);
}
inline void SPFA(int c){
    memset(dis,0x3F,sizeof(dis));
    memset(vis,false,sizeof(vis));
    vis[c]=true;
    queue<int> Q;
    Q.push(c);
    dis[c]=0LL;
    while(!Q.empty()){
        int x=Q.front();
        Q.pop();
        for(edge_t *k=p[x].nxt;k!=NULL;k=k->nxt)
            if(k->block)
                continue;
            else if(dis[k->dat]>dis[x]+k->len){
                dis[k->dat]=dis[x]+k->len;
                if(!vis[k->dat]){
                    vis[k->dat]=true;
                    Q.push(k->dat);
                }
            }
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#else
    freopen("tiger.in","r",stdin);
    freopen("tiger.out","w",stdout);
#endif
    scanf("%d%d%d",&n,&m,&k);
    top=n;
    for(int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        if(x!=y)
            add_edge(x+1,y+1,z);
    }
    for(int i=1,x;i<=k;i++){
        scanf("%d",&x);
        escape[x+1]=true;
    }
    dfs(1);
    SPFA(1);
    for(int i=1;i<=n;i++)
        if(escape[i])
            ans=min(dis[i],ans);
    printf("%lld\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#else
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}