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

```

