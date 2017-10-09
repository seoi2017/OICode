//SGU-275[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//15ms,0.4MB(354KB),1364B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cstring>
#define MX 128
using namespace std;
typedef long long ll_t;
ll_t tmp,ans;
int mt[MX][MX],n,m;
inline void Gauss(){
    for(int i=1,j=1;i<=n,j<=m;i++,j++){
        int index=i;
        for(int k=i;k<=n;k++)
            if(mt[k][j])index=k;
        if(!mt[index][j])
            {i--;continue;}
        if(index!=i)
            for(int k=1;k<=m;k++)
                swap(mt[index][k],mt[i][k]);
        for(int k=1;k<=n;k++)
            if(mt[k][j] && k!=i)
                for(int l=1;l<=m;l++)
                    mt[k][l]^=mt[i][l];
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    while(scanf("%d",&n)!=EOF){
        ans=0,m=0;
        for(int i=1,j=1;i<=n;i++,j=1){
            scanf("%lld",&tmp);
            while(tmp)
                mt[i][j++]=tmp&1,tmp>>=1;
            m=max(m,j-1);
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m/2;j++)
                swap(mt[i][j],mt[i][m-j+1]);
        Gauss();
        for(int i=1;i<=m;i++,tmp=0LL){
            ans<<=1;
            for(int j=1;j<=n;j++)
                tmp^=mt[j][i];
            ans|=tmp;
        }
        printf("%lld\n",ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}