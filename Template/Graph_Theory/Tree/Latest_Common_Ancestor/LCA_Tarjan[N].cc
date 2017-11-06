#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define N 500007
#define M 23
using namespace std;
struct edge_t{
    int dat;
    edge_t *nxt;
}p[(N<<1)+N];
inline void add_edge(int x,int y){
    p[++top].dat=y,p[top].nxt=p[x].nxt,p[x].nxt=&p[top];
    p[++top].dat=x,p[top].nxt=p[y].nxt,p[y].nxt=&p[top];
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d%d%d",&n,&m,&s);
    for(int i=1,x,y;i<n;i++){
        scanf("%d%d",&x,&y);
        add_edge(x,y);
    }//TODO
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}