#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 200005
#define lc (now<<1)
#define rc (now<<1|1)
#define mid ((l+r)>>1)
#define len (r-l+1)
using namespace std;
int n,m,val[N];
int top,dat[N+(N<<1)],nxt[N+(N<<1)];
inline void add_edge(int x,int y){
    dat[++top]=y;
    nxt[top]=nxt[x];
    nxt[x]=top;
}
namespace tree{
    int tot[N<<2],lazy[N<<2],lcol[N<<2],rcol[N<<2];
    inline void config(int now){
        if(!lazy[now])
            return;
        lazy[lc]=lazy[now];
        lazy[rc]=lazy[now];
        tot[lc]=tot[rc]=1;
        lcol[lc]=rcol[lc]=lazy[now];
        lcol[rc]=rcol[rc]=lazy[now];
        lazy[now]=0;
    }
    inline void refresh(int now){
        lcol[now]=lcol[lc];
        rcol[now]=rcol[rc];
        tot[now]=tot[lc]+tot[rc];
        if(rcol[lc]==lcol[rc])
            --tot[now];
    }
    void build(int now,int l,int r){
        if(l==r){
            tot[now]=1;
            lcol[now]=rcol[now]=val[l];
            return;
        }
        build(lc,l,mid);
        build(rc,mid+1,r);
        refresh(now);
    }
    void update(int now,int l,int r,int L,int R,int c){
        if(L<=l && r<=R){
            tot[now]=1;
            lazy[now]=c;
            lcol[now]=rcol[now]=c;
            return;
        }
        config(now);
        if(L<=mid)
            update(lc,l,mid,L,R,c);
        if(R>mid)
            update(rc,mid+1,r,L,R,c);
        refresh(now);
    }
    int query(int now,int l,int r,int L,int R){
        if(L<=l && r<=R)
            return tot[now];
        config(now);
        int ans=0;
        if(L<=mid)
            ans+=query(lc,l,mid,L,R);
        if(R>mid)
            ans+=query(rc,mid+1,r,L,R);
        refresh(now);
        if(L<=mid && R>mid && rcol[lc]==lcol[rc])
            --ans;
        return ans;
    }
    int get_col(int now,int l,int r,int pos){
        if(l==r)
            return lcol[now];
        config(now);
        if(pos<=mid)
            return get_col(lc,l,mid,pos);
        else
            return get_col(rc,mid+1,r,pos);
    }
}
namespace chain{
    using namespace tree;
    int id[N],son[N],fa[N],size[N],ct[N],deep[N],cnt=0;
    void dfs_1(int x,int f,int d){
        deep[x]=d,size[x]=1,fa[x]=f;
        int maxson=-1,y;
        for(int k=nxt[x];k;k=nxt[k]){
            y=dat[k];
            if(y==f)
                continue;
            dfs_1(y,x,d+1);
            size[x]+=size[y];
            if(size[y]>maxson)
                son[x]=y,maxson=size[y];
        }
    }
    void dfs_2(int x,int chain_top){
        val[id[x]=++cnt]=dat[x];
        ct[x]=chain_top;
        if(!son[x])
            return;
        dfs_2(son[x],chain_top);
        for(int k=nxt[x];k;k=nxt[k]){
            int y=dat[k];
            if(y==fa[x] || y==son[x])
                continue;
            dfs_2(y,y);
        }
    }
    void change(int x,int y,int c){
        while(ct[x]!=ct[y]){
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            update(1,1,n,id[ct[x]],id[x],c);
            x=fa[ct[x]];
        }
        if(deep[x]>deep[y])
            swap(x,y);
        update(1,1,n,id[x],id[y],c);
    }
    int ask(int x,int y){
        int ans=0,nx,fx;
        while(ct[x]!=ct[y]){
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            ans+=query(1,1,n,id[ct[x]],id[x]);
            nx=get_col(1,1,n,id[ct[x]]);
            fx=get_col(1,1,n,id[fa[ct[x]]]);
            if(nx==fx)
                --ans;
            x=fa[ct[x]];
        }
        if(deep[x]>deep[y])
            swap(x,y);
        ans+=query(1,1,n,id[x],id[y]);
        return ans;
    }
};
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    top=n;
    for(int i=1;i<=n;++i)
        scanf("%d",&dat[i]);
    for(int i=1,x,y;i<n;++i){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    chain::dfs_1(1,0,1);
    chain::dfs_2(1,1);
    tree::build(1,1,n);
    char c[4];
    for(int i=1,x,y,z;i<=m;++i){
        scanf("%s%d%d",&c,&x,&y);
        if(c[0]=='Q')
            printf("%d\n",chain::ask(x,y));
        else{
            scanf("%d",&z);
            chain::change(x,y,z);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}