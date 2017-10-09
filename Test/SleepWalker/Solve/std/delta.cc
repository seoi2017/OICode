//Problem.D Code By HYS.
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
const int prime[10]={3,13,31,131,313,1313,3131,13131,31313,131313};
int n,m,a[1024],b[100007],ind[3000003],has[3000003],req,tmp;
char str[16];
inline int strhash(const char* s){
    int t=0;//局部变量必须初始化！
    for(int i=0;i<strlen(s);i++)
        t+=(s[i]-13)*prime[i];
    return t%1313131+1;
}
int main(){
    freopen("delta.in","r",stdin);
    freopen("delta.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%s",str),a[i]=strhash(str),ind[a[i]]=2;
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%s",str),tmp=strhash(str);
        if(ind[tmp]!=0)b[i]=tmp;
        if(ind[tmp]==2)ind[tmp]=1,req++;
    }
    if(req==0)
        printf("0\n0\n");
    else{
        printf("%d\n",req);
        sort(a+1,a+1+n);
        int p=req,l=1,r=1,ans=0x3f3f3f3f;
        while(true){
            if(p==0){
                while(b[l]==0)l++;
                ans=min(ans,r-l);
                if(has[b[l]]<=1)p++;
                has[b[l]]--,l++;
            }
            else{
                if(r>m)break;
                if(ind[b[r]]!=0){
                    has[b[r]]++;
                    if(has[b[r]]==1)
                        p--;
                }
                r++;
            }
        }
        printf("%d\n",ans);
    }
    fclose(stdin);
    fclose(stdout);
    return 0;
}