//HDU-3359[Accepted]
//tag:[高斯消元（线性代数）]
//Code By HYS.
//249ms,3.8MB(3844KB),1925B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MX 512
#define eps 1e-8
#define INF 0x3f3f3f3f
using namespace std;
int h,w,d,pos[MX][MX],n=0,o;
double mt[MX][MX],a[MX][MX];
inline int MHT(int x0,int y0,int x1,int y1){
    return abs(x1-x0)+abs(y1-y0);
}
inline void Gauss(){ 
    for(int i=1;i<=n;i++){
        int index=i;
        for(int j=i+1;j<=n;j++)
            if(abs(mt[j][i])-abs(mt[index][i])>eps)index=j;
        if(abs(mt[index][i])<eps)continue;
        if(index!=i)
            for(int j=1;j<=n+1;j++)
                swap(mt[index][j],mt[i][j]);
        for(int j=1;j<=n;j++)
            if(mt[j][i] && j!=i){
                double temp=mt[j][i]/mt[i][i];
                for(int k=i;k<=n+1;k++)
                    mt[j][k]-=temp*mt[i][k];
            }
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    int tag=true;
    while(scanf("%d%d%d",&w,&h,&d)&&(h+w+d)){
        tag?tag=false:printf("\n");
        n=0;
        for(int i=1;i<=h;i++)
            for(int j=1;j<=w;j++)
                scanf("%lf",&a[i][j]),pos[i][j]=++n;
        memset(mt,0,sizeof(mt));
        for(int i=1;i<=h;i++)
            for(int j=1;j<=w;j++)
                for(int k=1;k<=h;k++)
                    for(int l=1;l<=w;l++)
                        if(MHT(i,j,k,l)<=d){
                            mt[pos[i][j]][pos[k][l]]=1.0;
                            mt[pos[i][j]][n+1]+=a[i][j];
                        }
        Gauss();
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                o=(i-1)*w+j;
                printf("%8.2lf",mt[o][n+1]/mt[o][o]);
            }
            printf("\n");
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}