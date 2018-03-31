#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 16
using namespace std;
int n,f[N][N][N][N];
//i:当前处理数位,j:模13的值,k:是否已经包含13,z:尾数
int dfs(int pos,int num,bool t,int e,bool flag){
    if(pos==-1)
        return
    if(!flag && f[pos][num][t][e]!=-1)
    return ans;
}
inline void solve(){
    int pos=0;
    while(n){
        bit[pos++]=n%10;
        n/=10;
    }
    return dfs(pos-1,0,0,0,1);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    menset(f,-1,sizeof(f));
    while(scanf("%d",&n))
        printf("%d\n",solve());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}