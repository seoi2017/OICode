#include<cstring>
#include<cstdio>
#include<algorithm>
#include<iostream>
#define maxn 504561
using namespace std;
int head[maxn*2];
long long a[maxn*2];
int n,m,s,num;
long long ans=0;
bool vis[maxn];
struct point
{int to,next,dis;}e[maxn*2];
void add(int from,int to,int dis)
{
    e[++num].next=head[from];
    e[num].to=to;
    e[num].dis=dis;
    head[from]=num;
}
void dfs(int u)
{
    vis[u]=1;
    int cnt=0;
    for(int i=head[u];i!=0;i=e[i].next)
    {
        int to=e[i].to;
        if(!vis[to])
        {
                dfs(to);
               if(a[to]+e[i].dis>a[u])
               {
                   ans+=(a[to]+e[i].dis-a[u])*cnt;
                   cnt++;
                   a[u]=a[to]+e[i].dis;
               }
               else
               {
                   ans+=a[u]-a[to]-e[i].dis;
                   cnt++;
               }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<n;i++)
    {int x,y,z;
    scanf("%d%d%d",&x,&y,&z);
    add(x,y,z);add(y,x,z);}
    memset(vis,0,sizeof(vis));
    dfs(s);
    printf("%lld",ans);
    return 0;
}
