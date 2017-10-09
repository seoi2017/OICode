//POJ-1288[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//32ms,0.7MB(740KB),1723B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
#define MX 64
using namespace std;
int T,p,n,mt[MX][MX],a[MX];
bool dfs(int x){
    if(x<0)return true;
    for(int i=0;i<3;i++){
        if(mt[x][x]*i%p==mt[x][n])return dfs(x-1);
    }
    return false;
}
inline bool Gauss(){
    int i=0,r=n;
    for(int j=0;i<n,j<r;i++,j++){
        int index=i;
        for(int k=i+1;k<n;k++)
            if(mt[k][j]>mt[index][j])index=k;
        if(!mt[index][j]){
            for(int k=1;k<n;k++)
                swap(mt[k][j],mt[r-1][j]);
            i--,r--;
            continue;
        }
        if(index!=i)
            for(int k=j;k<=n;k++)
                swap(mt[i][k],mt[index][k]);
        for(int k=0;k<n;k++)
            if(mt[k][j] && k!=i)
                for(int l=j,t=mt[k][j];l<=n;l++){
                    mt[k][l]=(mt[k][l]*mt[i][j]%p)-(mt[i][l]*t%p);
                    mt[k][l]=(mt[k][l]%p+p)%p;
                }
    }
    for(int k=i;k<n;k++)
        if(mt[k][n])return false;
    return dfs(i-1);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&T);
    while(T--){
        memset(mt,0,sizeof(mt));
        scanf("%d%d",&p,&n);
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<n;i++){
            for(int j=0;j<=i;j++)
                mt[i][j]=a[i-j];
            for(int j=i+1;j<n;j++)
                mt[i][j]=a[n-j];
        }
        mt[0][n]=1;
        if(Gauss())
            printf("A solution can be found\n");
        else
            printf("No solution\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}