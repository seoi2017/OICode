//POJ-2065[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//47ms,0.8MB(764KB),1776B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MX 128
using namespace std;
//这道题是从零开始计算的,和以前不一样,请注意.
int T,P,n,mt[MX][MX];
char str[MX];
inline int find(int x,int y){
    //((i+P)*x)%P=(i*x+P*x)%P=((i*x)%P+(P*x)%P)%P=((i*x)%P+0)%P=((i*x)%P)%P=(i*x)%P  (0<=i<P)
    int a=(x%P+P)%P,b=(y%P+P)%P;//第一个%P:使绝对值小于P;+P:负数变正数,正数超过P;第二个%P,大于P的正数再变回去
    for(int i=0;i<P;i++)
        if((i*a)%P==b)return i;
}
inline void Gauss(){
    for(int i=0;i<n;i++){
        int index=i;
        for(int j=i+1;j<n;j++)
            if(mt[j][i]>mt[index][i])index=j;
        if(index!=i)
            for(int j=0;j<=n;j++)
                swap(mt[i][j],mt[index][j]);
        for(int k=0;k<n;k++)
            if(mt[k][i] && k!=i)
                for(int j=0,tmp=mt[k][i];j<=n;j++)//大坑注意:mt[k][i]在消元过程中是会变化的!所以必须预先存起来!不能直接调用!
                    mt[k][j]=(mt[k][j]*mt[i][i]-mt[i][j]*tmp)%P;
    }
    for(int i=0;i<n;i++)
        mt[i][n]=find(mt[i][i],mt[i][n]);
}
int main(){
#ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    scanf("%d",&T);
    while(T--){
        scanf("%d",&P);
        scanf("%s",str);
        n=strlen(str);
        memset(mt,0,sizeof(mt));
        for(int i=0;i<n;i++)
            mt[i][n]=str[i]=='*'?0:str[i]-'a'+1;
        int tmp=0;
        for(int i=0;i<n;i++){
            tmp=1;
            for(int j=0;j<n;j++)
                mt[i][j]=tmp,tmp=(tmp*(i+1))%P;
        }
        Gauss();
        for(int i=0;i<n-1;i++)
            printf("%d ",mt[i][n]);
        printf("%d\n",mt[n-1][n]);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}