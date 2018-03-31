#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,sqn,ans;
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&n);
    sqn=sqrt(n);
    for(int i=1;i<=sqn;++i)
        for(int j=i;j<=n;++j)
        {
            if(i*j>n)
                break;
            ans+=2;
            if(i==j)
                --ans;
        }
    printf("%d",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}