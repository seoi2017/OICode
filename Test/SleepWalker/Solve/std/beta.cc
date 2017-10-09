//Problem.B Code By HYS.
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#define MX 128
using namespace std;
char str[MX*8];
int k,a[MX],p[MX],o[MX],tmp[MX],ans[MX];
//a：累乘器，p：原数，o：上一位的累乘器
inline bool judge(int x){
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=k;i++)//高精乘
        for(int j=1;j<=k;j++){
            if(i+j-1>k)break;
            tmp[i+j-1]+=a[i]*p[j];//若累乘器*原数=原数，则循环
            tmp[i+j]+=tmp[i+j-1]/10;
            tmp[i+j-1]%=10;
        }
    if(tmp[x]==p[x])return true;
    return false;
}
inline bool mul(){
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=k;i++)//高精乘
        for(int j=1;j<=k;j++){
            if(i+j-1>k)break;
            tmp[i+j-1]+=o[i]*a[j];
            tmp[i+j]+=tmp[i+j-1]/10;
            tmp[i+j-1]%=10;
        }
    for(int i=1;i<=k;i++)
        a[i]=tmp[i];//累乘器更新
}
inline void update(int x){
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=ans[0];i++)
        tmp[i]+=ans[i]*x,tmp[i+1]+=tmp[i]/10,tmp[i]%=10;
    for(int t=ans[0]+2;ans[0]<=t;ans[0]++)
        if(tmp[ans[0]]>=10)
            tmp[ans[0]+1]+=tmp[ans[0]]/10,tmp[ans[0]]%=10;
    while(tmp[ans[0]]==0)ans[0]--;
    for(int i=1;i<=ans[0];i++)
        ans[i]=tmp[i];
}
int main(){
    freopen("beta.in","r",stdin);
    freopen("beta.out","w",stdout);
    scanf("%s",str);
    scanf("%d",&k);
    int len=strlen(str);
    if(k>len+1)goto tag;//高位补零下不可能循环
    for(int i=len-1,j=1;i>=len-k;i--,j++)
        p[j]=o[j]=a[j]=str[i]-'0';
    ans[0]=ans[1]=1;
    for(int i=1;i<=k;i++){
        if(judge(i))continue;//判断第i位是否循环
        register int j;
        for(j=2;j<=10;j++){
            mul();//十次幂不循环必不循环
            if(judge(i))break;
        }
        if(j>=11)goto tag;
        update(j);//更新答案为ans*j
        for(j=1;j<=k;j++)
            o[j]=a[j];//更新上一位的累乘器
    }
    for(int i=ans[0];i;i--)
        printf("%d",ans[i]);
    if(false){
        tag:;
        printf("-1");
    }
    printf("\n");
    fclose(stdin);
    fclose(stdout);
    return 0;
}