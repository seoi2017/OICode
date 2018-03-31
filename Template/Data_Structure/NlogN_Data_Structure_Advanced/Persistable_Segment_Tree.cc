#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 1000007
#define mid ((l+r)>>1)
using namespace std;
int n,m;
struct node_t{
    node_t *lc,*rc;
    int dat;
}seg[N<<4],*root[N];
int top,ver;
node_t *build(int l,int r){
    node_t *now=&seg[++top];
    if(l==r)
        scanf("%d",&now->dat);
    else{
        now->lc=build(l,mid);
        now->rc=build(mid+1,r);
    }
    return now;
}
node_t *update(node_t *old,int pos,int val,int l,int r){
    node_t *now=&seg[++top];
    if(l==r){
        now->dat=val;
        return now;
    }
    now->lc=old->lc;
    now->rc=old->rc;
    if(pos<=mid)
        now->lc=update(old->lc,pos,val,l,mid);
    else
        now->rc=update(old->rc,pos,val,mid+1,r);
    return now;
}
int query(node_t *now,int l,int r,int pos){
    if(l==r)
        return now->dat;
    if(pos<=mid)
        return query(now->lc,l,mid,pos);
    else
        return query(now->rc,mid+1,r,pos);
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    root[0]=build(1,n);
    for(int i=1,v,com,pos,val;i<=m;++i){
        scanf("%d%d",&v,&com);
        if(com==1){
            scanf("%d%d",&pos,&val);
            root[++ver]=update(root[v],pos,val,1,n);
        }
        else{
            scanf("%d",&pos);
            root[++ver]=root[v];
            printf("%d\n",query(root[v],1,n,pos));
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}