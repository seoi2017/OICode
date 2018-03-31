//BZOJ会RE,不知为何,也许是动态指针的问题
//动态指针在释放内存时一定要先赋值为NULL
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 100007
#define mid ((l+r)>>1)
#define strin(x) string x;cin>>x;
using namespace std;
namespace var
{
    int n,m,w[N],c[N],top;
    int dat[N+(N<<1)],nxt[N+(N<<1)];
    inline void add_edge(int x,int y)
    {
        dat[++top]=y;
        nxt[top]=nxt[x];
        nxt[x]=top;
    }
}
namespace tree
{
    struct node_t
    {
        int sum,max;
        node_t *lc,*rc;
    }*root[N];
    inline void refresh(node_t *&now)
    {
        if(!now->lc && !now->rc)
        {
            now=NULL;
            delete now;
            return;
        }
        now->sum=(now->lc?now->lc->sum:0)+(now->rc?now->rc->sum:0);
        now->max=max(now->lc?now->lc->max:0,now->rc?now->rc->max:0);
    }
    void update(node_t *&now,int l,int r,int pos,int v)
    {
        if(!now)
            now=new node_t();
        if(l==r)
        {
            now->sum=now->max=v;
            return;
        }
        if(pos<=mid)
            update(now->lc,l,mid,pos,v);
        else
            update(now->rc,mid+1,r,pos,v);
        refresh(now);
    }
    void erase(node_t *&now,int l,int r,int pos)
    {
        if(l==r)
        {
            now=NULL;
            delete now;
            return;
        }
        if(pos<=mid)
            erase(now->lc,l,mid,pos);
        else
            erase(now->rc,mid+1,r,pos);
        refresh(now);
    }
    int query(node_t *now,int l,int r,int L,int R,bool is)
    {
        if(!now)
            return 0;
        if(L<=l && r<=R)
            return is?now->sum:now->max;
        int ans=0;
        if(is)
        {
            if(L<=mid)
                ans+=query(now->lc,l,mid,L,R,is);
            if(R>mid)
                ans+=query(now->rc,mid+1,r,L,R,is);
        }
        else
        {
            if(L<=mid)
                ans=max(ans,query(now->lc,l,mid,L,R,is));
            if(R>mid)
                ans=max(ans,query(now->rc,mid+1,r,L,R,is));
        }
        return ans;
    }
}
namespace chain
{
    using namespace var;
    int deep[N],fa[N],son[N],ct[N],size[N],id[N],cnt=0;
    void dfs_1(int x,int f,int d)
    {
        size[x]=1,fa[x]=f,deep[x]=d;
        int maxson=-1,y;
        for(int k=nxt[x];k;k=nxt[k])
        {
            y=dat[k];
            if(y==f)
                continue;
            dfs_1(y,x,d+1);
            size[x]+=size[y];
            if(size[y]>maxson)
                son[x]=y,maxson=size[y];
        }
    }
    void dfs_2(int x,int chain_top)
    {
        id[x]=++cnt;
        ct[x]=chain_top;
        if(!son[x])
            return;
        dfs_2(son[x],chain_top);
        for(int k=nxt[x],y;k;k=nxt[k])
        {
            y=dat[k];
            if(y==fa[x] || y==son[x])
                continue;
            dfs_2(y,y);
        }
    }
}
namespace solve
{
    using namespace tree;
    using namespace chain;
    inline void init()
    {
        for(int i=1;i<=n;++i)
            update(root[c[i]],1,n,id[i],w[i]);
    }
    inline void change_rig(int x,int y)
    {
        erase(root[c[x]],1,n,id[x]);
        c[x]=y;
        update(root[c[x]],1,n,id[x],w[x]);
    }
    inline void change_val(int x,int y)
    {
        w[x]=y;
        update(root[c[x]],1,n,id[x],w[x]);
    }
    inline int query_sum(int x,int y)
    {
        int ans=0,rig=c[x];
        while(ct[x]!=ct[y])
        {
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            ans+=query(root[rig],1,n,id[ct[x]],id[x],true);
            x=fa[ct[x]];
        }
        if(deep[x]>deep[y])
            swap(x,y);
        return ans+query(root[rig],1,n,id[x],id[y],true);
    }
    inline int query_max(int x,int y)
    {
        int ans=0,rig=c[x];
        while(ct[x]!=ct[y])
        {
            if(deep[ct[x]]<deep[ct[y]])
                swap(x,y);
            ans=max(ans,query(root[rig],1,n,id[ct[x]],id[x],false));
            x=fa[ct[x]];
        }
        if(deep[x]>deep[y])
            swap(x,y);
        return max(ans,query(root[rig],1,n,id[x],id[y],false));
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    using namespace solve;
    scanf("%d%d",&n,&m);
    top=n;
    for(int i=1;i<=n;++i)
        scanf("%d%d",&w[i],&c[i]);
    for(int i=1,x,y;i<n;++i)
    {
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    dfs_1(1,0,1);
    dfs_2(1,1);
    init();
    for(int i=1,x,y;i<=m;++i)
    {
        strin(s);
        scanf("%d%d",&x,&y);
        if(s=="QS")
            printf("%d\n",query_sum(x,y));
        else if(s=="QM")
            printf("%d\n",query_max(x,y));
        else if(s=="CC")
            change_rig(x,y);
        else if(s=="CW")
            change_val(x,y);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}