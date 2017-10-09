//POJ-1830[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//16ms,0.7MB(704KB),1486B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define MX 35
using namespace std;
int a[MX],mt[MX][MX],b,T,n;
inline int Gauss(){
    int i=1;
    for(int j=1;i<=n,j<=n;i++,j++){
        int index=i;
        for(int k=i+1;k<=n;k++)
            if(mt[k][j]>mt[i][j])index=k;
        if(!mt[index][j]){
            i--;
            /*
            当当前列无对应主元时，应尝试继续在当前行搜索下一个主元；
            若不这么做而直接跳过该行，最后所有的自由元（全零）方程不能集中在最后几行，导致结果出错
            */
            continue;
        }
        if(index!=i)
            for(int k=1;k<=n+1;k++)
                swap(mt[i][k],mt[index][k]);
        for(int k=1;k<=n;k++)
            if(mt[k][j] && k!=i)
                for(int l=1;l<=n+1;l++)
                    mt[k][l]^=mt[i][l];
    }
    for(int k=i;k<=n;k++)
        if(mt[k][n+1])return -1;
    return 1<<(n-i+1);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&T);
    while(T--){
        memset(mt,0,sizeof(mt));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++){
            scanf("%d",&b);
            mt[i][i]=1;
            mt[i][n+1]=b^a[i];
        }
        int ta,tb;
        while(scanf("%d%d",&ta,&tb)&&(ta+tb))
            mt[tb][ta]=1;
        int ans=Gauss();
        if(ans==-1)printf("Oh,it's impossible~!!\n");
        else printf("%d\n",ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}