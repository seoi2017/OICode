#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
#define N 2007
using namespace std;
struct p_t
{
    p_t(int x,int y):val(x),len(y){}
    int val,len;
};
stack<p_t> S;
int n,m,a[N][N],f0[N][N],f1[N][N],h0[N][N],h1[N][N];
inline int solve_square()
{
    int ans=0;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(a[i][j]==0)
                ans=max(ans,f0[i][j]=min(f0[i-1][j-1],min(f0[i-1][j],f0[i][j-1]))+1);
            else
                ans=max(ans,f1[i][j]=min(f1[i-1][j-1],min(f1[i-1][j],f1[i][j-1]))+1);
    return ans*ans;
}
inline int solve_rectangle()
{
    int ans=0;
    //solve 0
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(a[i][j]==0)
                h0[i][j]=h0[i-1][j]+1;
            else
                h0[i][j]=0;
    for(int i=1,len;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            len=0;
            while(!S.empty() && S.top().val>=h0[i][j])
            {
                S.top().len+=len;
                ans=max(ans,S.top().val*S.top().len);
                len=S.top().len;
                S.pop();
            }
            S.push(p_t(h0[i][j],len+1));
        }
        len=0;
        while(!S.empty())
        {
            S.top().len+=len;
            ans=max(ans,S.top().val*S.top().len);
            len=S.top().len;
            S.pop();
        }
    }
    //solve 1
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if(a[i][j]==1)
                h1[i][j]=h1[i-1][j]+1;
            else
                h1[i][j]=0;
    for(int i=1,len;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            len=0;
            while(!S.empty() && S.top().val>=h1[i][j])
            {
                S.top().len+=len;
                ans=max(ans,S.top().val*S.top().len);
                len=S.top().len;
                S.pop();
            }
            S.push(p_t(h1[i][j],len+1));
        }
        len=0;
        while(!S.empty())
        {
            S.top().len+=len;
            ans=max(ans,S.top().val*S.top().len);
            len=S.top().len;
            S.pop();
        }
    }
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            scanf("%d",&a[i][j]);
    for(int i=1;i<=n;++i)
        for(int j=1;j<=m;++j)
            if((i+j)%2==0)
                a[i][j]=!a[i][j];
    printf("%d\n",solve_square());
    printf("%d\n",solve_rectangle());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}