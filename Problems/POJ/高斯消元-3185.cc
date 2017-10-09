//POJ-3185[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//0ms,0.7MB(704KB),1610B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define INF 0x3f3f3f3f
#define MX 32
using namespace std;
int n=20,mt[MX][MX],freeyuan[MX],x[MX];
inline int Gauss(){
    int i=1,t=0;
    for(int j=1;i<=n,j<=n;i++,j++){
        int index=i;
        for(int k=i+1;k<=n;k++)
            if(mt[k][j]>mt[index][j])index=k;
        if(!mt[index][j]){
            freeyuan[++t]=j,i--;
            continue;
        }
        if(index!=i)
            for(int k=1;k<=n+1;k++)
                swap(mt[index][k],mt[i][k]);
        for(int k=1;k<=n;k++)
            if(mt[k][j] && i!=k)
                for(int l=1;l<=n+1;l++)
                    mt[k][l]^=mt[i][l];
    }
    //必须注明的一点：结束消元后，i指针指向的是第一个自由元（全零）方程
    for(int k=i;k<=n;k++)
        if(mt[k][n+1])return -1;
    int res=INF;
    int s=(1<<t);
    for(int k=0;k<s;k++){
        int cnt=0;
        for(int j=1;j<=t;j++)
            if(x[freeyuan[j]]=(bool)(k&(1<<(j-1))))cnt++;
        for(int j=i-1;j>=1;j--){//所以第i-1个方程才是最后一个非自由元（全零）方程
            int tmp=mt[j][n+1];
            for(int l=j+1;l<=n;l++)
                tmp^=(mt[j][l]&x[l]);
            if(x[j]=tmp)cnt++;
        }
        res=min(res,cnt);
    }
    return res;
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    for(int i=1;i<=n;i++)
        scanf("%d",&mt[i][n+1]),mt[i][i]=1;
    for(int i=2;i<n;i++)
        mt[i-1][i]=mt[i+1][i]=1;
    mt[2][1]=mt[n-1][n]=1;
    printf("%d\n",Gauss());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}