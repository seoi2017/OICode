//HDU-3364[Accepted]
//tag:[高斯消元（线性代数）]
//Code By HYS.
//249ms,1.7MB(1704KB),1762B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define MX 64
#define eps 1e-8
#define INF 0x3f3f3f3f
using namespace std;
int T,cases,n,m,q,mtx[MX][MX],mt[MX][MX];
inline void matrix_copy(){
    memset(mt,0,sizeof(mt));//非常重要,如果不加这句就会WA
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m+1;j++)
            mt[i][j]=mtx[i][j];
}
inline long long Gauss(){
    int i=1;
    for(int l=1;l<=m;l++){
        int index=i;
        for(int j=i+1;j<=n;j++)
            if(mt[j][l]>mt[index][l])index=j;
        if(!mt[index][l])
            continue;
        if(index!=i)
            for(int j=1;j<=m+1;j++)
                swap(mt[index][j],mt[i][j]);
        for(int k=1;k<=n;k++)
            if(mt[k][l] && k!=i)
                for(int j=1;j<=m+1;j++)
                    mt[k][j]^=mt[i][j];
        i++;
    }
    for(int j=i;j<=n;j++)
        if(mt[j][m+1])return 0LL;
    return 1LL<<(m-i+1);
}
int main(){
#ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    scanf("%d",&T);
    while(T--){
        memset(mtx,0,sizeof(mtx));
        scanf("%d%d",&n,&m);
        int a,b;
        for(int i=1;i<=m;i++){
            scanf("%d",&a);
            for(int j=1;j<=a;j++){
                scanf("%d",&b);
                mtx[b][i]=1;
            }
        }
        scanf("%d",&q);
        printf("Case %d:\n",++cases);
        for(int i=1;i<=q;i++){
            matrix_copy();
            for(int i=1;i<=n;i++)
                scanf("%d",&mt[i][m+1]);
            printf("%lld\n",Gauss());
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}