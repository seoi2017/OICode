#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define lc 0
#define rc 1
#define N 100007
using namespace std;
struct node_t{
    int val,size,sum,lx,rx,mx;
    bool rev,tag;
    node_t *son[2],*fa;
};
node_t node[N],*root,*lroot;
int n,m,top;
//Memory Protected Functions
inline int size(node_t *t){return !t?0:t->size;}
inline int sum(node_t *t){return !t?0:t->sum;}
inline int mx(node_t *t){return !t?0:t->mx;}
inline int lx(node_t *t){return !t?0:t->lx;}
inline int rx(node_t *t){return !t?0:t->rx;}
//Splay Functions
inline node_t *newnode(int val,node_t *fa){
    node_t *now=&node[++top];
    now->val=val,now->fa=fa,now->rev=false;
    now->size=1,now->son[lc]=now->son[rc]=NULL;
    return now;
}
inline void reverse(node_t *t){
    if(t)
        t->rev^=1;
}
inline void pushup(node_t *t){
    node_t *ls=t->son[lc],*rs=t->son[rc];
    t->size=1+size(ls)+size(rs);
    t->sum=t->val+sum(ls)+sum(rs);
    t->mx=max(max(mx(ls),mx(rs)),rx(ls)+t->val+lx(rs));
    t->lx=max(lx(ls),sum(ls)+t->val+lx(rs));
    t->rx=max(rx(rs),sum(rs)+t->val+rx(ls));
}
inline void pushdown(node_t *t){
    if(!t)
        return;
    node_t *ls=t->son[lc],*rs=t->son[rc];
    if(t->tag){
        t->rev=t->tag=0;
        if(ls)
            ls->tag=1,ls->val=t->val,ls->sum=t->val*ls->size;
        if(rs)
            rs->tag=1,rs->val=t->val,rs->sum=t->val*rs->size;
        if(t->val>=0){
            if(ls)
                ls->lx=ls->rx=ls->mx=ls->sum;
            if(rs)
                rs->lx=rs->rx=rs->mx=rs->sum;
        }
        else{
            if(ls)
                ls->lx=ls->rx=0,ls->mx=t->val;
            if(rs)
                rs->lx=rs->rx=0,rs->mx=t->val;
        }
    }
    if(t->rev){
        t->rev^=1;
        if(ls)
            swap(ls->lx,ls->rx);
        if(rs)
            swap(rs->lx,rs->rx);
        reverse(ls),reverse(rs);
        swap(ls,rs);
        
    }
}
inline bool get_son(node_t *t,node_t *f){
    return f && f->son[rc]==t;
}
inline void connect(node_t *t,node_t *f,bool k){
    if(!f)
        root=t;
    else
        f->son[k]=t;
    if(t)
        t->fa=f;
}
inline void rorate(node_t *t){
    node_t *f=t->fa;
    node_t *g=f->fa;
    bool a=get_son(t,f),b=!a;
    connect(t->son[b],f,a);
    connect(t,g,get_son(f,g));
    connect(f,t,b);
    pushup(f);
    pushup(t);
}
inline void splay(node_t *t,node_t *p){
    while(t->fa!=p){
        node_t *f=t->fa;
        node_t *g=f->fa;
        pushdown(g);
        pushdown(f);
        pushdown(t);
        if(g==p)
            rorate(t);
        else{
            if(get_son(f,g)^get_son(t,f))
                rorate(t),rorate(t);
            else
                rorate(f),rorate(t);
        }
    }
}
inline void insert(node_t *r,int val){
    if(r==NULL)
        r=newnode(val,NULL);
    else{
        node_t *t=r;
        while(t->son[rc]!=NULL)
            t=t->son[rc];
        splay(t,NULL);
        t->son[rc]=newnode(val,t);
        pushup(r);
        splay(t->son[rc],NULL);
    }
}
inline node_t *kth(node_t *r,int rank){
    node_t *now=r;
    while(now){
        pushdown(now);
        if(size(now->son[lc])<rank){
            rank-=size(now->son[lc]);
            if(rank==1)
                return now;
            else
                --rank,now=now->son[rc];
        }
        else
            now=now->son[lc];
    }
}
inline node_t *split(int k,int tot){
    node_t *l=kth(root,k),*r=kth(root,k+tot+1);
    splay(l,root);
    splay(r,root->son[rc]);
    return root->son[rc]->son[lc];
}
inline void query(int k,int tot){
    node_t *t=split(k,tot);
    printf("%d\n",t->sum);
}
inline void fan(int k,int tot){
    node_t *t=split(k,tot);
    if(t && !t->tag){
        t->rev^=1;
        swap(t->lx,t->rx);
        swap(t->son[lc],t->son[rc]);
        pushup(t);
        if(t->fa)
            pushup(t->fa);
    }
}
inline void erase(int k,int tot){
    node_t *t=split(k,tot);
    t->fa->son[lc]=NULL;
    pushup(t->fa);
    if(t->fa->fa)
        pushup(t->fa->fa);
}
inline void build(){
    
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif

#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}