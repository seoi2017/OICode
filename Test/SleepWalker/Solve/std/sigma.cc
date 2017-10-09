//Problem.E Code By HYS.
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#define INF 0x3f3f3f3f
#define MX 1024
using namespace std;
int n,m,k,a[MX][MX],d[MX][MX],dis[MX],x,y,l;
bool vis[MX];
inline int spfa(){
    queue<int> Q;
    Q.push(1);
    memset(vis,false,sizeof(vis));
    vis[1]=true;
    memset(dis,0x3f,sizeof(dis));
    dis[1]=0;
    while(!Q.empty()){
        int x=Q.front();
        Q.pop();
        vis[x]=false;
        for(int i=1;i<=n;i++)
            if(d[x][i]!=INF && dis[x]+d[x][i]<dis[i]){
                dis[i]=dis[x]+d[x][i];
                if(!vis[i])Q.push(i),vis[i]=true;
            }
    }
    return dis[n]==INF?-1:dis[n];
}
int main(){
    freopen("sigma.in","r",stdin);
    freopen("sigma.out","w",stdout);
    memset(a,0x3f,sizeof(a));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&x,&y,&l),a[x][y]=a[y][x]=min(a[x][y],l);
    for(int i=1;i<=n;i++)
        a[i][i]=INF;
    int l=0,r=1000001,ans;
    while(l<=r){
        ans=(l+r)>>1;
        memset(d,0x3f,sizeof(d));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j]=(a[i][j]==INF?INF:a[i][j]>ans?1:0);
        int res=spfa();
        if(res==-1){
            l=-1;
            break;
        }
        if(res>k)l=ans+1;
        else if(res<=k)r=ans-1;
    }
    printf("%d\n",l);//最后输出什么要注意，不同的二分方式最后的输出是不同的
    fclose(stdin);
    fclose(stdout);
    return 0;
}