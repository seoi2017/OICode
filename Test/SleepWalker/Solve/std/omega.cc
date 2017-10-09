//Problem.F Code By HYS.
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define MX 500007
#define ES 500000
#define INF 0x3F3F3F3F
using namespace std;
int n,k,tmp,f[MX],af[MX],bf[MX],a[MX],b[MX],val[MX<<1];
char c[4];
struct node_t{
    int l,r,s;
};
class seg_t{
private:
    node_t seg[MX<<4];
public:
    void build(int,int,int);
    void change(int,int,int);
    int query(int,int,int);
    inline void pushup(int);
}segtree;
void seg_t::build(int x,int l,int r){
    seg[x].l=l,seg[x].r=r,seg[x].s=INF;
    if(l==r)return;
    int mid=l+((r-l)>>1);
    build(x<<1,l,mid);
    build((x<<1)|1,mid+1,r);
}
void seg_t::change(int x,int c,int s){
    if(seg[x].l==c && seg[x].r==c){
        seg[x].s=s;
        return;
    }
    int mid=seg[x].l+((seg[x].r-seg[x].l)>>1);
    if(c<=mid)change(x<<1,c,s);
    else change((x<<1)|1,c,s);
    pushup(x);
}
int seg_t::query(int x,int l,int r){
    if(seg[x].l==l && seg[x].r==r)
        return seg[x].s;
    int mid=seg[x].l+((seg[x].r-seg[x].l)>>1);
    if(r<=mid)return query(x<<1,l,r);
    else if(l>mid)return query((x<<1)|1,l,r);
    else return min(query(x<<1,l,mid),query((x<<1)|1,mid+1,r));
}
inline void seg_t::pushup(int x){
    seg[x].s=min(seg[x<<1].s,seg[(x<<1)|1].s);
}
int main(){
    freopen("omega.in","r",stdin);
    freopen("omega.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%s",c),tmp=c[0]-'A'+1;
        a[i]=a[i-1]+(tmp==1);
        b[i]=b[i-1]+(tmp==2);
    }
    memset(af,0x3F,sizeof(af));
    memset(bf,0x3F,sizeof(bf));
    memset(val,0x3F,sizeof(val));
    val[ES]=af[0]=bf[0]=f[0]=0;
    segtree.build(1,-500000,500000);
    segtree.change(1,0,0);
    int x,y,z;
    for(int i=1;i<=n;i++){
        x=af[a[i]],y=bf[b[i]];
        z=segtree.query(1,a[i]-b[i]-k,a[i]-b[i]+k);
        f[i]=min(min(x+1,y+1),min(z+1,f[i-1]+1));
        af[a[i]]=min(af[a[i]],f[i]);
        bf[b[i]]=min(bf[b[i]],f[i]);
        if(f[i]<val[a[i]-b[i]+ES]){
            val[a[i]-b[i]+ES]=f[i];
            segtree.change(1,a[i]-b[i],f[i]);
        }
    }
    printf("%d\n",f[n]);
    fclose(stdin);
    fclose(stdout);
    return 0;
}