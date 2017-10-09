//Problem.A Code By HYS.
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define MX 20
using namespace std;
int a[MX][MX],f[MX][MX];
//DP:f[i][j]表示已经选了i列，最后一列是j的最小答案
int n,m,r,c,ans=1<<30;
int w[MX],v[MX][MX],vis[MX];//行间差W，任意两列间差V
void dp(){
    memset(f,0x3f,sizeof(f));
    memset(w,0,sizeof(w));
    memset(v,0,sizeof(v));
    for(int i=1;i<=m;i++)//每一列
        for(int j=1;j<r;j++)//vis[j]表示已被选中的行
            w[i]=w[i]+abs(a[vis[j]][i]-a[vis[j+1]][i]);//计算行间差
    for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++)
            for(int k=1;k<=r;k++)
                v[i][j]=v[i][j]+abs(a[vis[k]][i]-a[vis[k]][j]);//计算任意两列间的列间差
    f[0][0]=0;//重要的初始化
    for(int i=1;i<=c;i++)//选了i列
        for(int j=i;j<=m;j++)//最后一列为j
            for(int k=0;k<j;k++)//上一次选了k列
                f[i][j]=min(f[i-1][k]+w[j]+v[k][j]/**/,f[i][j]);
    for(int i=c;i<=m;i++)
        ans=min(ans,f[c][i]);//更新答案
}
void dfs(int x,int y){
    if(y>r){//已经选择了r行
        dp();
        return;
    }
    if(x>n)return;
    dfs(x+1,y);//不选择该行
    vis[y]=x;//选择的第y行为x
    dfs(x+1,y+1);//选择该行
}
int main(){
    freopen("alpha.in","r",stdin);
    freopen("alpha.out","w",stdout);
    scanf("%d%d%d%d",&n,&m,&r,&c);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    dfs(1,1);
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}