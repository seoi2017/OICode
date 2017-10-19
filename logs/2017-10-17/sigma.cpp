#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n;
long long ans;
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#else
    freopen("sigma.in","r",stdin);
    freopen("sigma.out","w",stdout);
#endif
    scanf("%d",&n);
    for(int i=1,j;i<=n;i++)
        if(i&1)ans+=i;
        else{
            j=i; 
            while(!(j&1)){
                j>>=1;
            }
            ans+=j;
        }
    printf("%lld\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#else
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}