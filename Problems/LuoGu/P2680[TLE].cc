//T到怀疑人生,不过BZOJ过了
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 300007
#define lgN 19
using namespace std;
int st[N][lgN+1],deep[N],ln[N][lgN+1],faln[N];
struct edge_t{
    int dat,len;
    edge_t *nxt;
}e[N+(N<<1)];
struct question_t{
    int x,y,len,lca;
    bool operator<(const question_t &x)const{
        return this->len<x.len;
    }
}q[N];
int top,n,m;
inline void add_edge(int x,int y,int z){
    edge_t *now=&e[++top];
    now->dat=y,now->len=z;
    now->nxt=e[x].nxt;
    e[x].nxt=now;
}
void build(int x,int d){
    deep[x]=d;
    for(edge_t *k=e[x].nxt;k;k=k->nxt)
        if(k->dat!=st[x][0]){
            st[k->dat][0]=x;
            ln[k->dat][0]=k->len;
            build(k->dat,d+1);
        }
        else
            faln[x]=k->len;
}
int lca(int x,int y,int &len){
    if(deep[x]<deep[y])
        swap(x,y);
    for(int k=lgN;k>=0;--k)
        if(deep[st[x][k]]>=deep[y])
            len+=ln[x][k],x=st[x][k];
    if(x==y)
        return x;
    for(int k=lgN;k>=0;--k)
        if(st[x][k]!=st[y][k]){
            len+=(ln[x][k]+ln[y][k]);
            x=st[x][k],y=st[y][k];
        }
    len+=(ln[x][0]+ln[y][0]);
    return st[x][0];
}
int c[N];//差分数组
void sum(int x){//差分数组转标准数组
    for(edge_t *k=e[x].nxt;k;k=k->nxt)
        if(k->dat!=st[x][0]){
            sum(k->dat);
            c[x]+=c[k->dat];
        }
}
bool check(int x){//差分检查
    memset(c,0,sizeof(c));
    int tot=0,mxl=0,mxr=0;
    for(int i=1;i<=m;++i)
        if(q[i].len>x){
            ++tot;
            mxl=max(mxl,q[i].len);
            ++c[q[i].x],++c[q[i].y];
            c[q[i].lca]-=2;
        }
    sum(1);
    for(int i=2;i<=n;++i)
        if(c[i]==tot)
            mxr=max(mxr,faln[i]);
    return mxl-mxr<=x;
}
namespace readin{
    inline char readc(){ 
        static char buf[1<<18],*fs,*ft;
        return (fs==ft && (ft=(fs=buf)+fread(buf,1,1<<18,stdin)),fs==ft)?EOF:*fs++;
    }
    inline int readint(){
        char c;int r;
        while(c=readc()){if(c>='0' && c<='9'){r=c^0x30;break;}}
        while(isdigit(c=readc()))r=(r<<3)+(r<<1)+(c^0x30);
        return r;
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    //scanf("%d%d",&n,&m);
    n=readin::readint();
    m=readin::readint();
    top=n;
    for(int i=1,x,y,z;i<n;++i){
        //scanf("%d%d%d",&x,&y,&z);
        x=readin::readint();
        y=readin::readint();
        z=readin::readint();
        add_edge(x,y,z);
        add_edge(y,x,z);
    }
    st[1][0]=1;
    build(1,0);
    for(int k=1;k<=lgN;++k)
        for(int i=1;i<=n;++i){
            st[i][k]=st[st[i][k-1]][k-1];
            ln[i][k]=ln[st[i][k-1]][k-1]+ln[i][k-1];
        }
    for(int i=1;i<=m;++i){
        //scanf("%d%d",&q[i].x,&q[i].y);
        q[i].x=readin::readint();
        q[i].y=readin::readint();
        q[i].lca=lca(q[i].x,q[i].y,q[i].len);
    }
    sort(q+1,q+1+m);
    int l=0,r=q[m].len,mid,ans;
    while(l<=r){
        mid=(l+r)>>1;
        if(check(mid))
            r=mid-1,ans=mid;
        else
            l=mid+1;
    }
    printf("%d\n",ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}