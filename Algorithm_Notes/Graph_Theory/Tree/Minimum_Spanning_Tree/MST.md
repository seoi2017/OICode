# 图论 - 最小生成树

## 概述

一个有$N$个结点的连通图的生成树是原图的极小连通子图，且包含原图中的所有$N$个结点，并且有保持图连通的最少的边。

在一给定的无向图$G=(V, E)$，$(u, v)$代表连接顶点$u$与顶点$v$的边，而$w(u, v)$代表此边的权重，若存在$T$为$E$的子集且为无循环图，使得$w(T)$最小，则此$T$为$G$的最小生成树。

最小生成树其实是最小权重生成树的简称。

## 算法

最小生成树（MST）可通过Prim或Kruskal算法求出，各算法的复杂度如下：

|   算法    |              时间复杂度              |
| :-----: | :-----------------------------: |
|  Prim   | $邻接表：O(Elog_2V)\\\\邻接矩阵：O(V^2)$ |
| Kruskal |          $O(Elog_2E)$           |

## 原理

### Kruskal

### Prim

## 实现（[洛谷P3366][https://www.luogu.org/problem/show?pid=3366#sub "洛谷题目链接"]）

### Kruskal实现

```cpp
//Template:Kruskal(MST)
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#define N 5003
#define M 200007
using namespace std;
typedef long long ll_t; //有些时候需要长整数型存边权
bool visit[N];          //访问数组，多组数据时记得清空
struct edge_t           //Kruskal存边的结构体
{
    int start, end; //起止点
    ll_t length;    //边权
} e[M];
int n, m, cnt;                                    //边数统计器
int father[N], ranking[N];                        //并查集父节点数组、按秩合并数组
ll_t tot_length;                                  //MST总长度
inline bool cmp(const edge_t &x, const edge_t &y) //结构体按边权排序
{
    return x.length < y.length;
}
int find_father(int x) //找到祖先节点，附带路径压缩
{
    return father[x] == x ? x : father[x] = find_father(father[x]);
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        father[i] = i, ranking[i] = 1; //初始化父节点和秩数组
    for (int i = 1; i <= m; i++)
        scanf("%d%d%lld", &e[i].start, &e[i].end, &e[i].length);
    sort(e + 1, e + 1 + m, cmp); //按边权从小到大排序
    for (int i = 1; i <= m; i++) //枚举边
    {
        int x = find_father(e[i].start), y = find_father(e[i].end);
        if (x == y) //若该边的两个端点已经合并过则跳过
            continue;
        if (ranking[x] < ranking[y]) //按秩合并
            swap(x, y);
        father[y] = x;
        ranking[x] += ranking[y];
        tot_length += e[i].length; //更新生成树长度
        cnt++;                     //生成树内边数量+1
        if (cnt == n - 1)          //已求出生成树
            break;
    }
    cnt < n - 1 ? printf("orz\n") : printf("%lld\n", tot_length); //最终边数量不足n-1则无解
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
}
```

### Prim实现

```cpp
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
```

