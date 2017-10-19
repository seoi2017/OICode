#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<map>
#define N 200007
using namespace std;
map<pair<char,int>,bool> ind;
int n,m,p,ans;
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#else
    freopen("lazer.in","r",stdin);
    freopen("lazer.out","w",stdout);
#endif
    scanf("%d%d%d",&n,&m,&p);
    ans=p;
    for(int i=1,x,y;i<=p;i++){
        scanf("%d%d",&x,&y);
        map<pair<char,int>,bool>::iterator itx=ind.find(make_pair('X',x)),ity=ind.find(make_pair('Y',y));
        if(itx!=ind.end() || ity!=ind.end()) 
            ans--;
        ind[make_pair('X',x)]=true;
        ind[make_pair('Y',y)]=true;
    }
    printf("%d\n",ans-1);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#else
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}