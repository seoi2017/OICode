#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<bitset>
#define P 100000000
#define N 16
using namespace std;
int n,m,f[N][1<<N],can[N],pre[1<<N],cnt,ans;
inline bool judge(int x)
{
    return !(x&(x>>1));
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;++i)
        for(int j=1;j<=m;++j)
        {
            scanf("%d",&x);
            if(!x)
                can[i]|=(1<<(m-j));
        }
    for(int i=0;i<(1<<m);++i)
        if(judge(i))
            pre[++cnt]=i;
    /*
    //查看二进制表示可使用bitset
    for(int i=1;i<=cnt;++i)
        cout<<bitset<sizeof(int)>(pre[i])<<endl;
    */
    for(int i=1;i<=cnt;++i)
        if(!(can[1]&pre[i]))
            f[1][i]=1;
    for(int i=2;i<=n;++i)
        for(int j=1;j<=cnt;++j)
            if(!(pre[j]&can[i-1]))
                for(int k=1;k<=cnt;++k)
                    if(!(can[i]&pre[k]) && !(pre[k]&pre[j]))
                        f[i][k]=(f[i][k]+f[i-1][j])%P;
    for(int i=1;i<=cnt;++i)
        ans=(ans+f[n][i])%P;
    printf("%d\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}