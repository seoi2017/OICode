//POJ-2947[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//2079ms,1.7MB(1716KB),2044B
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define MX 512//记得看好数据范围
using namespace std;
const char *date[7]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
int n,m,p,tmp,mt[MX][MX];
char sday[4],eday[4];
inline int Gdate(char *str){
    for(int i=0;i<7;i++)
        if(!strcmp(date[i],str))return i+1;
}
inline int find(int a,int b){
    for(int i=3;i<=9;i++)//注意解的范围
        if((a*i)%7==b)return i;
}
inline int Gauss(){
    //if(m<n)return -1;//这句话看起来是"方程数量不足,解不出来,无解"的意思,其实是错的
    int i=1;//M行N列,N+1增广
    for(int j=1;i<=m,j<=n;j++){
        int index=i;
        for(int k=i+1;k<=m;k++)
            if(abs(mt[k][j])>abs(mt[index][j]))index=k;
        if(mt[index][j]==0)
            continue;
        if(index!=i)
            for(int k=1;k<=n+1;k++)
                swap(mt[i][k],mt[index][k]);
        for(int l=1;l<=m;l++)
            if(mt[l][j] && l!=i)
                for(int t=mt[l][j],k=1;k<=n+1;k++)
                    mt[l][k]=t*mt[i][k]-mt[l][k]*mt[i][j],mt[l][k]=(mt[l][k]%7+7)%7;;
        i++;
    }
    for(int k=i;k<=m;k++)
        if(mt[k][n+1])return -1;//无解
    if(i-1!=n)return 1;//有自由元,多解
    return 0;//有唯一解
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    while(scanf("%d%d",&n,&m)&&(n+m)){
        memset(mt,0,sizeof(mt));
        for(int i=1;i<=m;i++){
            scanf("%d %s %s",&p,sday,eday);
            mt[i][n+1]=(Gdate(eday)-Gdate(sday)+1+7)%7;
            for(int j=1;j<=p;j++)
                scanf("%d",&tmp),mt[i][tmp]=(mt[i][tmp]+1)%7;
        }
        tmp=Gauss();
        if(tmp<0)printf("Inconsistent data.\n");
        else if(tmp>0)printf("Multiple solutions.\n");
        else{
            for(int i=1;i<n;i++)
                printf("%d ",find(mt[i][i],mt[i][n+1]));
            printf("%d\n",find(mt[n][n],mt[n][n+1]));
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}