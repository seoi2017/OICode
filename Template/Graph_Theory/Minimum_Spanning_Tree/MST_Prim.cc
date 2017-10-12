//Template:Prim(MST)
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 5003
#define M 200007
#define INF 0x3F3F3F3F3F3F3F3F //长整数型INF
using namespace std;
typedef long long ll_t;
struct edge_t
{ //邻接表结构体
    int dat;
    ll_t len;
    edge_t *nxt;
} p[N + (M * 2)]; //无向图双向存边，记得开双倍，再加上N个起始点，统共N+(M*2)个
struct node_t
{ //优先队列结构体
    int dat;
    ll_t len;
    node_t(int x, ll_t l)
    { //构造函数
        this->dat = x, this->len = l;
    }
    bool operator<(const node_t &x) const
    {
        return x.len < this->len; //由于使用默认的大根堆，要想变为小根堆就要反过来比
    }
};
ll_t dis[N], ans; //距离已选节点距离的数组、答案变量
int top, n, m;    //top用于存边
bool vis[N];      //访问数组，记录节点是否已选
inline void add_edge(int x, int y, ll_t l)
{ //邻接表加边
    p[++top].dat = y, p[top].len = l, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
    p[++top].dat = x, p[top].len = l, p[top].nxt = p[y].nxt, p[y].nxt = &p[top];
}
inline int prim(int c)
{                                   //普利姆算法主体
    memset(dis, 0x3F, sizeof(dis)); //所有节点到已选节点的距离设为INF
    priority_queue<node_t> Q;       //优先队列
    Q.push(node_t(c, dis[c] = 0));  //第一个选择的节点距离设为0
    int cnt = 0;                    //已选节点计数器，最终为n则有解
    while (!Q.empty())
    {
        node_t x = Q.top(); //取小根堆堆顶元素
        Q.pop();
        if (x.len != dis[x.dat])
            continue;        //若已被更新，说明有更优解，舍去
        vis[x.dat] = 1;      //标记为已访问
        ans += x.len, cnt++; //已选节点加一，更新答案
        for (edge_t *k = p[x.dat].nxt; k != NULL; k = k->nxt)
        { //更新未选节点到已选节点的距离
            if (!vis[k->dat] && dis[k->dat] > k->len)
            {                                   //如果未被访问且有更优解
                dis[k->dat] = k->len;           //更新距离
                Q.push(node_t(k->dat, k->len)); //压入优先队列
            }
        }
    }
    return cnt; //返回在生成树内的节点数量
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    top = n; //已有的n个起始点
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d%lld", &x, &y, &ans);
        add_edge(x, y, ans); //无向图双向加边
    }
    ans = 0LL; //由于上面偷懒用了ans读入，计算生成树前必须清零
    prim(1) == n ? printf("%lld\n", ans) : printf("orz\n");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}