#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int n,m,tag,tot;
char s[4];
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
    }*root;
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
    inline void insert(int val)
    { //插入一个值(可重复)
        if(root==NULL)
        {
            root=new node_t(val);
            return;
        }
        node_t *x=root,*f=root;
        while(x)
            f=x,x=x->son[val>=x->dat];
        f->son[val>=f->dat]=x=new node_t(val,f);
        splay(x,NULL);
    }
    inline node_t *kth(int rank)
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
    inline void erase(int val)
    { //删除值小于val的节点
        node_t *t=root,*ft=root;
        while(t)
        {
            if(t->dat<val)
                t=t->son[1];
            else
                ft=t,t=t->son[0];
        }
        if(ft->dat<val)
        {
            root=NULL;
            //delete root;
        }
        splay(ft,NULL);
        ft->son[0]=NULL;
        //delete ft->son[0];
        refresh(ft);
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
        scanf("%s%d",s,&x);
        if(s[0]=='I')
        {
            if(x>=m)
                ++tot,insert(x-tag);
        }
        else if(s[0]=='A')
            tag+=x;
        else if(s[0]=='S')
            tag-=x,erase(m-tag);
        else if(s[0]=='F')
        {
            if(size(root)<x)
                printf("-1\n");
            else
                printf("%d\n",kth(size(root)-x+1)->dat+tag);
        }
    }
    printf("%d\n",tot-size(root));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}