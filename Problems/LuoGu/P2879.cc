#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#define N 1000007
using namespace std;
map<pair<int,int>,bool> ind;
int n,I,mxh,m;
namespace bitree{
    int c[N]={0};
    inline int lowbit(int x){
        return x&(-x);
    }
    inline void add(int x,int s){
        for(int i=x;i<=n;i+=lowbit(i))
            c[i]+=s;
    }
    inline int sum(int x){
        int ans=0;
        for(int i=x;i;i-=lowbit(i))
            ans+=c[i];
        return ans;
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    using namespace bitree;
    scanf("%d%d%d%d",&n,&I,&mxh,&m);
    for(int i=1,x,y;i<=m;++i){
        scanf("%d%d",&x,&y);
        if(y>x)
            swap(x,y);
        if(ind.find(make_pair(x,y))==ind.end()){
            add(x,1);
            add(y+1,-1);
            ind[make_pair(x,y)]=true;
        }
    }
    for(int i=1;i<=n;++i)
        printf("%d\n",mxh+sum(i));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}