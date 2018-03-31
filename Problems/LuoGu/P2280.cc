#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 5007
using namespace std;
int v[N][N],n,r,ans;
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&r);
    for(int i=1,x,y,z;i<=n;++i)
    {
        scanf("%d%d",&x,&y);
        scanf("%d",&z);
        v[x+1][y+1]+=z;
    }
    for(int i=1;i<=5001;++i)
        for(int j=1;j<=5001;++j)
            v[i][j]+=(v[i-1][j]+v[i][j-1]-v[i-1][j-1]);
    for(int i=r;i<=5001;++i)
        for(int j=r;j<=5001;++j)
            ans=max(ans,v[i][j]-v[i-r][j]-v[i][j-r]+v[i-r][j-r]);
    printf("%d\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}