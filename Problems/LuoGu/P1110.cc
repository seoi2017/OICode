//本来应该使用平衡树的,我偷了个懒...
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<set>
#define instr(s) string s;cin>>s;
#define N 500007
#define INF 0x3f3f3f3f
using namespace std;
typedef multiset<int> tree_t;
int st[N],et[N];
tree_t A,B;
tree_t::iterator it;
int n,m,ans1=INF,ans2=INF;
inline void update_ans1(int x,int y)
{
    if(!st[x])
    {
        st[x]=y,et[x]=y;
        A.insert(abs(st[x]-et[x-1]));
        return;
    }
    A.erase(A.find(abs(st[x+1]-et[x])));
    A.insert(abs(y-et[x]));
    A.insert(abs(y-st[x+1]));
    et[x]=y;
    ans1=*A.begin();
}
inline void update_ans2(int x)
{
    B.insert(x);
    it=B.find(x);
    ans2=min(ans2,min(abs(*(++it)-*(--it)),abs(*(--it)-*(++it))));
}
int main()
{
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    ios::sync_with_stdio(false);
    cin>>n>>m;
    st[0]=et[0]=st[n+1]=et[n+1]=INF;
    B.insert(-INF),B.insert(INF);
    for(int i=1,x;i<=n;++i)
    {
        cin>>x;
        update_ans1(i,x);
        update_ans2(x);
    }
    A.insert(abs(st[n+1]-et[n]));
    ans1=*A.begin();
    for(int i=1,x,y;i<=m;++i)
    {
        instr(s);
        if(s=="INSERT")
        {
            cin>>x>>y;
            update_ans1(x,y);
            update_ans2(y);
        }
        else if(s=="MIN_GAP")
            cout<<ans1<<endl;
        else if(s=="MIN_SORT_GAP")
            cout<<ans2<<endl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}