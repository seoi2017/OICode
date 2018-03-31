//值得思考的一道题,正解是二阶差分,很不幸我不会,所以只能用数学方法推导,所幸做出来了
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 500007
using namespace std;
long long n,m[N],k,p,over,cnt,ext,i,i2;
long long hp[N],num[N];
inline bool check(long long p)
{
    cnt=0;//统共放置子弹的数目
    memset(hp,0,sizeof(hp));//统共对某一位置造成的伤害
    memset(num,0,sizeof(num));//在该位置施放的子弹
    over=sqrt(p)+1;//子弹起效的最大范围
    ext=0;//合计溅射子弹数目
    i=i2=0;//sigma和sigma^2,拆分公式中的元素
    for(int j=n;j>=1;--j)
    { //从右到左检查
        if(num[j+1])
        { //上一个位置打出了子弹
            ext+=num[j+1];//加上溅射到该位置的子弹数目
            i+=num[j+1]*(j+1);//更新sigma值
            i2+=num[j+1]*(j+1)*(j+1);//更新sigma^2值
        }
        if((j+over<=n)&& num[j+over])
        { //如果有无效子弹
            ext-=num[j+over];
            i-=num[j+over]*(j+over);
            i2-=num[j+over]*(j+over)*(j+over);
        }
        hp[j]+=ext*p-i2+2*i*j-ext*j*j;//合计伤害
        if(hp[j]<m[j])
        { //没杀死
            num[j]+=ceil(double(m[j]-hp[j])/p);
            cnt+=num[j];
        }
        if(cnt>k)
            return false;
    }
    return true;
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&m[i]);
        ++m[i];
    }
    long long l=1,r=1e15,mid,ans;
    while(l<r)
    {
        mid=(l+r)>>1;
        if(check(mid))
            ans=mid,r=mid;
        else
            l=mid+1;
    }
    printf("%lld\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}