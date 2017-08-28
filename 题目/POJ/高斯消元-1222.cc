//POJ-1222[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//0ms,0.7MB(704KB),1993B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MX 32
using namespace std;
int n,mt[MX][MX];//第一维表示开关1~30；第二维表示灯1~30，结果31
inline void print(){//Debug Matrix Output
    printf("\n");
    for(int i=1;i<=30;i++){
        for(int j=1;j<=30;j++){
            printf("%d ",mt[i][j]);
        }
        printf("| %d\n",mt[i][31]);
    }
}
inline void Gauss(){
    int index;
    for(int i=1;i<=30;i++){
        index=i;
        for(int j=i+1;j<=30;j++){
            if(mt[i][i]<mt[j][i])index=j;
        }
        if(index!=i){
            for(int j=1;j<=31;j++){
                swap(mt[i][j],mt[index][j]);
            }
        }
        for(int j=1;j<=30;j++){
            if(mt[j][i] && j!=i){
                for(int k=1;k<=31;k++){
                    mt[j][k]^=mt[i][k];
                }
            }
        }
        //print();
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&n);
    int t=n;
    while(t--){
        memset(mt,0,sizeof(mt));
        for(int i=1;i<=30;i++){
            scanf("%d",&mt[0][i]);
            if(mt[0][i])mt[i][31]=1;
        }
        for(int i=1;i<=5;i++){
            for(int j=1;j<=6;j++){
                register int now=(i-1)*6+j;
                mt[now][now]=1;//自己对自己有影响
                if(j-1>0)mt[now][now-1]=1;//对左侧有影响
                if(j+1<7)mt[now][now+1]=1;//对右侧有影响
                if(i-1>0)mt[now][now-6]=1;//对上方有影响
                if(i+1<6)mt[now][now+6]=1;//对下方有影响
            }
        }
        Gauss();
        printf("PUZZLE #%d\n",n-t);
        for(int i=1;i<=30;i++){
            if(i%6==0)printf("%d\n",mt[i][31]);
            else printf("%d ",mt[i][31]);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
}