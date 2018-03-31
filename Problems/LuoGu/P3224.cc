#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 100007
using namespace std;
namespace var
{
    int n,m,fa[N],id[N];
    char c[4];
    int findfa(int x)
    {
        return fa[x]==x?x:fa[x]=findfa(fa[x]);
    }
}
namespace splay
{
    using namespace var;
    struct node_t
    {
        int dat,size;
        node_t *fa,*son[2];
        node_t(int x,node_t *f=NULL)
        {
            this->dat=x;
            this->fa=f;
            this->size=1;
            this->son[0]=this->son[1]=NULL;
        }
    }*tree[N];
    inline int size(node_t *x)
    {
        if(x)
            return x->size;
        return 0;
    }
    inline bool is_son(node_t *x)
    { //判断当前节点是父节点的左子节点还是右子节点
        if(!x->fa)
            return false;
        return x->fa->son[1]==x;
    }
    inline void refresh(node_t *x)
    { //更新节点大小信息
        x->size=1;
        if(x->son[0])
            x->size+=x->son[0]->size;
        if(x->son[1])
            x->size+=x->son[1]->size;
    }
    inline void connect(node_t *x,node_t *f,node_t *&root,bool is)
    { //建立从f到x的父子关系
        if(!f)
            root=x;
        else
            f->son[is]=x;
        if(x)
            x->fa=f;
    }
    inline void rorate(node_t *x,node_t *&root)
    { //将x节点旋转至父节点处
        node_t *f=x->fa,*g=f->fa;
        bool is=is_son(x),it=!is;
        connect(x->son[it],f,root,is);
        connect(x,g,root,is_son(f));
        connect(f,x,root,it);
        refresh(f);
        refresh(x);
    }
    inline void splay(node_t *x,node_t *y,node_t *&root)
    { //将x节点旋转至y节点的子节点,当需要旋转至根节点时y=NULL
        while(x->fa!=y)
        {
            node_t *f=x->fa,*g=f->fa;
            if(g==y)
                rorate(x,root);
            else
            {
                if(is_son(f)^is_son(x))
                    rorate(x,root);
                else
                    rorate(f,root);
                rorate(x,root);
            }
        }
    }
    inline void insert(node_t *&root,int val)
    { //插入一个值
        if(root==NULL)
            root=new node_t(val);
        for(node_t *x=root;x;x=x->son[val>=x->dat])
        {
            if(x->dat==val)
            {
                splay(x,NULL,root);
                return;
            }
            if(!x->son[val>=x->dat])
                x->son[val>=x->dat]=new node_t(val,x);
        }
    }
    void run(node_t *x,node_t *&to)
    { //暴力将所有节点插入另一棵splay
        if(x->son[0])
            run(x->son[0],to);
        if(x->son[1])
            run(x->son[1],to);
        insert(to,x->dat);
        x=NULL;
        delete x;
    }
    inline void print()
    {
        for(int i=1;i<=n;++i)
            printf("%d ",findfa(i));
        printf("\n");
        for(int i=1;i<=n;++i)
            printf("%d ",size(tree[findfa(i)]));
        printf("\n");
    }
    inline void merge(int x,int y)
    { //启发式合并两棵splay
        int fx=findfa(x),fy=findfa(y);
        if(fx==fy)
            return;
        if(size(tree[fx])<size(tree[fy]))
            swap(fx,fy);
        fa[fy]=fx;
        run(tree[fy],tree[fx]);
        //print();
    }
    inline node_t *kth(node_t *&root,int rank)
    { //求第k"小"
        node_t *x=root;
        while(x)
            if(size(x->son[0])<rank)
            {
                rank-=size(x->son[0]);
                if(rank==1)
                    break;
                else
                    --rank,x=x->son[1];
            }
            else
                x=x->son[0];
        return x;
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    using namespace splay;
    scanf("%d%d",&n,&m);
    for(int i=1,x;i<=n;++i)
    {
        fa[i]=i;
        scanf("%d",&x);
        id[x]=i;
        tree[i]=new node_t(x);
    }
    for(int i=1,x,y;i<=m;++i)
    {
        scanf("%d%d",&x,&y);
        merge(x,y);
    }
    scanf("%d",&m);
    for(int i=1,x,y;i<=m;++i)
    {
        scanf("%s%d%d",c,&x,&y);
        if(c[0]=='B')
            merge(x,y);
        else
        {
            node_t *ans=kth(tree[findfa(x)],y);
            printf("%d\n",ans?id[ans->dat]:-1);
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}