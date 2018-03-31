#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 505007
using namespace std;
int dat[N+(N<<1)],len[N+(N<<1)],nxt[N+(N<<1)],top;
int n,s;
bool vis[N];
long long mxl[N],ans;
inline void add_edge(int x,int y,int z)
{
    dat[++top]=y;
    len[top]=z;
    nxt[top]=nxt[x];
    nxt[x]=top;
}
void dp(int x)
{
    vis[x]=true;
    for(int k=nxt[x],y,cnt=0;k;k=nxt[k])
    {
        y=dat[k];
        if(vis[y])
            continue;
        dp(y);
        if(mxl[y]+len[k]>mxl[x])
        {
            ans+=(mxl[y]+len[k]-mxl[x])*cnt;
            mxl[x]=mxl[y]+len[k];
        }
        else
            ans+=mxl[x]-(mxl[y]+len[k]);
        ++cnt;
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&s);
    top=n;
    for(int i=1,x,y,z;i<n;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        add_edge(x,y,z);
        add_edge(y,x,z);
    }
    dp(s);
    printf("%lld\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}