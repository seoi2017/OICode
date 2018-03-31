//应离散化,但懒,故未离散化
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 1000007
using namespace std;
int n,m,blocks,sum,ans[N],tot[N],a[N];
struct q_t{
    int l,r,id;
    bool operator<(const q_t &x)const{
        return (l/blocks)==(x.l/blocks)?(r<x.r):(l/blocks)<(x.l/blocks);
    }
}q[N];
inline void add(int x){
    ++tot[x];
    if(tot[x]==1)
        ++sum;
}
inline void del(int x){
    --tot[x];
    if(tot[x]==0)
        --sum;
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    blocks=sqrt(m);
    for(int i=1;i<=m;++i){
        scanf("%d%d",&q[i].l,&q[i].r);
        q[i].id=i;
    }
    sort(q+1,q+1+m);
    for(int i=1,l=1,r=0;i<=m;++i){
        while(r<q[i].r)
            ++r,add(a[r]);
        while(r>q[i].r)
            del(a[r]),--r;
        while(l>q[i].l)
            --l,add(a[l]);
        while(l<q[i].l)
            del(a[l]),++l;
        ans[q[i].id]=sum;
    }
    for(int i=1;i<=m;++i)
        printf("%d\n",ans[i]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}