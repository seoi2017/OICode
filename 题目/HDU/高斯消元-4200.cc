//HDU-4200[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//15ms,1.7MB(1740KB),1902B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define MX 128
#define INF 0x3f3f3f3f
using namespace std;
int mt[MX][MX],T,n,d,x[MX];
inline int Gauss(){
    int i=1,t=0,r=n;
    for(int j=1;i<=n,j<=r;i++,j++){
        int index=i;
        for(int k=i+1;k<=n;k++)
            if(mt[k][j]>mt[index][j])index=k;
        if(!mt[index][j]){
            for(int k=1;k<=n;k++)//把自由元列移到最后
                swap(mt[k][j],mt[k][r]);
            t++,j--,i--,r--;
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
    for(int k=i;k<=n;k++)//别忘了无解情况！
        if(mt[k][n+1])return -1;
    int res=INF,s=(1<<t);
    for(int k=0;k<s;k++){
        int cnt=0;
        memset(x,0,sizeof(x));
        for(int j=1;j<=t;j++)
            if(x[i+j-1]=(bool)(k&(1<<(j-1))))cnt++;
        for(int j=i-1;j>=1;j--){
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
    scanf("%d",&T);
    while(T--){
        memset(mt,0,sizeof(mt));
        scanf("%d%d",&n,&d);
        for(int i=1;i<=n;i++)
            scanf("%d",&mt[i][n+1]);
        for(int i=1;i<=n;i++)
            for(int j=max(i-d,1);j<=min(i+d,n);j++)
                mt[j][i]=1;
        int ans=Gauss();
        if(ans!=-1)printf("%d\n",ans);
        else printf("impossible\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}