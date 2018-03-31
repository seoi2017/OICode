#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 80007
using namespace std;
int n,m,src[N];
char c[16];
namespace splay
{
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
    }*root,*pos[N];
    inline int size(node_t *x)
    { //取树大小
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
    inline void connect(node_t *x,node_t *f,bool is)
    { //建立从f到x的父子关系
        if(!f)
            root=x;
        else
            f->son[is]=x;
        if(x)
            x->fa=f;
    }
    inline void rorate(node_t *x)
    { //将x节点旋转至父节点处
        node_t *f=x->fa,*g=f->fa;
        bool is=is_son(x),it=!is;
        connect(x->son[it],f,is);
        connect(x,g,is_son(f));
        connect(f,x,it);
        refresh(f);
        refresh(x);
    }
    inline void splay(node_t *x,node_t *y)
    { //将x节点旋转至y节点的子节点,当需要旋转至根节点时y=NULL
        while(x->fa!=y)
        {
            node_t *f=x->fa,*g=f->fa;
            if(g==y)
                rorate(x);
            else
            {
                if(is_son(f)^is_son(x))
                    rorate(x);
                else
                    rorate(f);
                rorate(x);
            }
        }
    }
    node_t *build(int l,int r,node_t *f)
    { //根据已有序列建树
        if(l>r)
            return NULL;
        int mid=(l+r)>>1;
        node_t *x=new node_t(src[mid],f);
        pos[src[mid]]=x; //建立从编号到节点的索引
        x->son[0]=build(l,mid-1,x);
        x->son[1]=build(mid+1,r,x);
        refresh(x);
        return x;
    }
    inline int rank(node_t *x)
    { //求节点排名
        splay(x,NULL);
        return size(x->son[0])+1;
    }
    inline node_t *find(int rank)
    { //求第k大
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
    inline void reposition(int x,int y)
    { //将排名x的节点移到排名y
        splay(find(x-1),NULL);
        splay(find(x+1),root);
        node_t *tmp=root->son[1]->son[0];
        root->son[1]->son[0]=NULL;
        refresh(root->son[1]);
        refresh(root);
        splay(find(y-1),NULL);
        splay(find(y),root);
        connect(tmp,root->son[1],false);
        refresh(root->son[1]);
        refresh(root);
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
    for(int i=1;i<=n;++i)
        scanf("%d",&src[i]);
    root=build(0,n+1,NULL);
    for(int i=1,x,y;i<=m;++i)
    { //移动位置时不要忘记前后两个哨兵节点
        scanf("%s%d",c,&x);
        if(c[0]=='T')
            reposition(rank(pos[x]),2);
        else if(c[0]=='B')
            reposition(rank(pos[x]),n+1);
        else if(c[0]=='I')
        {
            scanf("%d",&y);
            if(y==0)
                continue;
            x=rank(pos[x]);
            reposition(x,x+y);
        }
        else if(c[0]=='A')
            printf("%d\n",rank(pos[x])-2);
        else if(c[0]=='Q')
            printf("%d\n",find(x+1)->dat);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}