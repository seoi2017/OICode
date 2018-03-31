#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<stack>
#define N 100007
using namespace std;
typedef long long ll_t;
struct p_t
{
    p_t(ll_t x,ll_t y):val(x),len(y){}
    ll_t val;
    ll_t len;
};
stack<p_t> S;
ll_t n,x,ans,len;
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    while(scanf("%lld",&n)!=EOF && n)
    {
        ans=0;
        for(int i=1;i<=n;++i)
        {
            scanf("%lld",&x);
            len=0;
            while(!S.empty() && S.top().val>=x)
            {
                S.top().len+=len;
                ans=max(ans,S.top().val*S.top().len);
                len=S.top().len;
                S.pop();
            }
            S.push(p_t(x,len+1));
        }
        len=0;
        while(!S.empty())
        {
            S.top().len+=len;
            ans=max(ans,S.top().val*S.top().len);
            len=S.top().len;
            S.pop();
        }
        printf("%lld\n",ans);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}