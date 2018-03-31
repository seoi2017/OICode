#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define INF 1e9
#define N 100007
#define M 5007
using namespace std;
struct s_t{
    int id,v;
}s[N];
struct q_t{
    int id,l,r,k;
}q[M];
int n,m,c[N];
inline bool cmp(const s_t &x,const s_t &y){
    return x.v<y.v;
}
inline int lowbit(int x){
    return -x&x;
}
inline void add(int x,int s){
    for(int i=x;i<=n;i+=lowbit(i))
        c[i]+=s;
}
inline int sum(int x){
    for(int i=x;i;i-=lowbit(i))
        ans+=c[i];
    return ans;
}
void erfen(int L,int R,int l,int r){
    if(L>R)
        return;
    for(int i=1;i<=n;++i)
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        s[i].id=i;
        scanf("%d",&s[i].v);
    }
    sort(s+1,s+1+n,cmp);
    for(int i=1;i<=m;++i){
        q[i].id=i;
        scanf("%d%d%d",&q[i].l,&q[i].r,&q[i].k);
    }
    erfen(1,m,-INF,INF);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}