#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 107
#define P 9999973
//#define C(x) (x*(x-1)/2) 没事别乱用宏,有重复计算的BUG
using namespace std;
typedef long long ll_t;
ll_t f[N][N][N],n,m,ans;
inline int C(ll_t x)
{
    return x*(x-1)/2;
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%lld%lld",&n,&m);
    f[0][0][0]=1;
    for(int i=0;i<n;++i)//第i列
        for(int j=0;j<=m;++j)//有j列放置一个棋子
            for(int k=0;j+k<=m;++k)//有k列放置两个棋子
            {
                if(!f[i][j][k])
                    continue;
                //啥也不放
                f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%P;
                //放一个,在没有棋子的位置
                if(m-j-k>0)
                    f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k]*(m-j-k))%P;
                //放一个,在有一个棋子的位置
                if(j>0)
                    f[i+1][j-1][k+1]=(f[i+1][j-1][k+1]+f[i][j][k]*j)%P;
                //放两个,都在没有棋子的位置
                if(m-j-k>1)
                    f[i+1][j+2][k]=(f[i+1][j+2][k]+f[i][j][k]*C(m-j-k))%P;
                //放两个,一个在有一个棋子的位置,另一个在没有棋子的位置
                if(j>0 && m-j-k>0)
                    f[i+1][j][k+1]=(f[i+1][j][k+1]+f[i][j][k]*j*(m-j-k))%P;
                //放两个,都在有一个棋子的位置
                if(j>1)
                    f[i+1][j-2][k+2]=(f[i+1][j-2][k+2]+f[i][j][k]*C(j))%P;
            }
    for(int i=0;i<=m;++i)
        for(int j=0;i+j<=m;++j)
            ans=(ans+f[n][i][j])%P;
    printf("%lld\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}