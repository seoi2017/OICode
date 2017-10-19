#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 500007
#define M 23
using namespace std;
struct edge_t{
    int dat;
    edge_t *nxt;
}p[(N<<1)+N];//树最多n-1条边，由于无向乘二，加上n个节点，共2n级别的数据量
int n,m,s,top,deep[N],st[N][M];
bool vis[N];
inline void add_edge(int x,int y){
    p[++top].dat=y,p[top].nxt=p[x].nxt,p[x].nxt=&p[top];
    p[++top].dat=x,p[top].nxt=p[y].nxt,p[y].nxt=&p[top];
}
void build(int x,int d){
    vis[x]=true,deep[x]=d;
    for(edge_t *k=p[x].nxt;k!=NULL;k=k->nxt)
        if(!vis[k->dat]){
            st[k->dat][0]=x;
            build(k->dat,d+1);
        }
}
inline int lca(int x,int y){
    if(deep[x]>deep[y])swap(x,y);
    int f=deep[y]-deep[x];
    for(int i=0;(1<<i)<=f;i++)
        if((1<<i)&f)y=st[y][i];
    if(x!=y){
        for(int i=20;i>=0;i--)
            if(st[x][i]!=st[y][i])
                x=st[x][i],y=st[y][i];
        x=st[x][0];
    }
    return x;
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d%d",&n,&m,&s);
    top=n;
    for(int i=1,x,y;i<n;i++){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
    }
    build(s,0);
    for(int j=1;(1<<j)<=n;j++)
        for(int i=1;i<=n;i++)
            st[i][j]=st[st[i][j-1]][j-1];
    for(int i=1,x,y;i<=m;i++){
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}