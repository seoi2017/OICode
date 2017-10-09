//HDU-3571[Accepted]
//tag:[高斯消元（线性代数）][扩展欧几里德（数论）]
//Code By HYS.
//312ms,1.8MB(1760KB),2446B
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MX 64
#define P 200000000000000003LL//模数2e17+3，仅能宏定义，不能const
#define D 100000000000000000LL//偏移量1e17，仅能宏定义，不能const
using namespace std;
typedef long long ll_t;
ll_t a[MX][MX],mt[MX][MX];
int T,n,cases;
inline ll_t mod(ll_t x){//减法模拟取模
    while(x>=P)x-=P;
    return x;
}
inline ll_t mul(ll_t x,ll_t y){//移位乘法（二分乘法），防止爆long long
    ll_t s;
    for(s=0;y;y>>=1){
        if(y&1)s=mod(s+x);
        x=mod(x+x);
    }
    return s;
}
void ExGCD(ll_t a,ll_t b,ll_t d,ll_t &x,ll_t &y){//扩展欧几里德
    if(!b)d=a,x=1,y=0;
    else ExGCD(b,a%b,d,y,x),y-=/*=-*/x*(a/b);//细节错误×1
}
inline ll_t inv(ll_t a,ll_t b){//求模b意义下逆元
    ll_t x,y,d;
    ExGCD(a,b,d,x,y);
    return (x%b+b)%b;
}
inline void Gauss(){
    ll_t v,tmp;
    for(int i=1;i<=n;i++){
        int index=i;
        for(int j=i+1;j<=n;j++)
            if(mt[j][i]>mt[index][i])index=j;
        if(index!=i)
            for(int j=i;j<=n+1;j++)
                swap(mt[i][j],mt[index][j]);
        v=inv(mt[i][i],P);
        for(int j=1;j<=n;j++)
            if(mt[j][i] && j!=i){
                tmp=mul(mt[j][i],v);//模P意义下的mt[j][i]/mt[i][i]
                for(int k=i;k<=n+1;k++){
                    mt[j][k]-=mul(tmp,mt[i][k]);
                    mt[j][k]=(mt[j][k]%P+P)%P;
                }
            }
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    ll_t tmp;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(a,0,sizeof(a));
        memset(mt,0,sizeof(mt));
        for(int i=1;i<=n+1;i++)
            for(int j=1;j<=n;j++){
                scanf("%lld",&a[i][j]);
                a[i][j]+=D,a[i][n+1]+=mul(a[i][j],a[i][j]);
                while(a[i][n+1]>=P)a[i][n+1]-=P;
            }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                tmp=a[i+1][j]-a[i][j];
                tmp=(tmp%P+P)%P;
                mt[i][j]=mul(tmp,2);
            }
            mt[i][n+1]=a[i+1][n+1]-/*=*/a[i][n+1];//细节错误×2
            mt[i][n+1]=(mt[i][n+1]%P+P)%/*&*/P;//细节错误×3
        }
        Gauss();
        printf("Case %d:\n%lld",++cases,mul(mt[1][n+1],inv(mt[1][1],P))-D);
        for(int i=2;i<=n;i++)
            printf(" %lld",mul(mt[i][n+1],inv(mt[i][i],P))-D);
        printf("\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}