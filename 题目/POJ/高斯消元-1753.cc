//POJ-1753[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//47ms,0.7MB(700KB),2426B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#define MX 24
#define INF 0x3f3f3f3f
using namespace std;
char c;
int mt1[MX][MX],mt2[MX][MX],x[MX],ans1,ans2,t,freeyuan[MX];
inline int Gauss(int mtx[MX][MX]){
    t=0;
    for(int i=1;i<=16;i++){
        int index=i;
        for(int j=i+1;j<=16;j++)
            if(mtx[j][i]>mtx[index][i])index=j;
        if(mtx[index][i]==0){l
            freeyuan[++t]=i;
            continue;
        }
        if(index!=i)
            for(int j=1;j<=17;j++)
                swap(mtx[i][j],mtx[index][j]);
        for(int j=1;j<=16;j++)
            if(mtx[j][i] && i!=j)
                for(int k=1;k<=17;k++)
                    mtx[j][k]^=mtx[i][k];
    }
    for(int i=17-t;i<=16;i++)
        if(mtx[i][17])return -1;
    int res=INF;
    int s=(1<<t);
    memset(x,0,sizeof(x));
    for(int i=0;i<s;i++){
        int cnt=0;
        for(int j=1;j<=t;j++)
        if(x[freeyuan[j]]=(bool)(i&(1<<(j-1))))cnt++;
        for(int j=16-t;j>=1;j--){
            int tmp=mtx[j][17];
            for(int k=j+1;k<=16;k++){
                tmp^=(mtx[j][k]&x[k]);
            }
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
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            scanf("%c",&c);
            c=='b'?mt1[(i-1)*4+j][17]=1:mt1[(i-1)*4+j][17]=0;
            c=='b'?mt2[(i-1)*4+j][17]=0:mt2[(i-1)*4+j][17]=1;
        }
        scanf("\n");
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            register int now=(i-1)*4+j;
            mt1[now][now]=mt2[now][now]=1;
            if(i-1>0)mt1[now-4][now]=mt2[now-4][now]=1;
            if(i+1<5)mt1[now+4][now]=mt2[now+4][now]=1;
            if(j-1>0)mt1[now][now-1]=mt2[now][now-1]=1;
            if(j+1<5)mt1[now][now+1]=mt2[now][now+1]=1;
        }
    }
    ans1=Gauss(mt1),ans2=Gauss(mt2);
    if(ans1==-1 && ans2==-1)
        printf("Impossible\n");
    /*万不可像下面这么写，因为一旦ans1!=-1，后面的Gauss(mt2)便不会执行！
    if((ans1=Gauss(mt1))==-1 && (ans2=Gauss(mt2))==-1)
        printf("Impossible\n");
    */
    else
        printf("%d\n",min(ans1,ans2));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}