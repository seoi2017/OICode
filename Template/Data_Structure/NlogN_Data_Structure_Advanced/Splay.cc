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
    int val,size;
    bool rev;
    node_t *son[2],*fa;
};
node_t node[N],*root;
int n,m,top;
inline int size(node_t *t){
    return !t?0:t->size;
}
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
    t->size=1;
    t->size+=size(t->son[lc]);
    t->size+=size(t->son[rc]);
}
inline void pushdown(node_t *t){
    if(!t || !t->rev)
        return;
    swap(t->son[lc],t->son[rc]);
    reverse(t->son[lc]);
    reverse(t->son[rc]);
    t->rev^=1;
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
inline void insert(int val){
    if(root==NULL)
        root=newnode(val,NULL);
    else{
        node_t *t=root;
        while(t->son[rc]!=NULL)
            t=t->son[rc];
        splay(t,NULL);
        t->son[rc]=newnode(val,t);
        pushup(root);
        splay(t->son[rc],NULL);
    }
}
inline node_t *kth(int rank){
    node_t *now=root;
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
inline void print(){
    for(int i=1;i<=n;++i)
        printf("%d ",kth(i+1)->val);
    printf("\n");
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for(int i=0;i<=n+1;++i)
        insert(i);
    for(int i=1,l,r;i<=m;++i){
        scanf("%d%d",&l,&r);
        ++l,++r;
        splay(kth(l-1),NULL);
        splay(kth(r+1),root);
        reverse(root->son[rc]->son[lc]);
    }
    print();
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}