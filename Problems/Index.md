$$
1st\ Law\ of\ NOIp\\ \quad P(x)=\frac{1}{\sum_{i\in OIer}F(x,i)}\quad (0\leqslant F(x,i)\leqslant 1)
$$

# 基础

## 模拟

## 暴力

## 贪心

## 高精度

```cpp
//压位高精度，MAX_SUM视题目而定。
const int base = 100000000;
const int power = 8;
class bigint_t
{
  public:
	long long s[MAX_SUM];
	bigint_t()
	{
		memset(this->s, 0, sizeof(this->s));
	}
	bigint_t(int x)
	{
		*this = x;
	}
	void operator=(const char *str)
	{
		memset(this->s, 0, sizeof(this->s));
		int len = strlen(str);
		this->s[0] = (len + power - 1) / power;
		for (int i = 0, t = 0, w; i < len; w *= 10, ++i)
		{
			if (i % power == 0)
				w = 1, ++t;
			this->s[t] += (w * (str[i] - '0'));
		}
	}
	void operator=(const int x)
	{
		memset(this->s, 0, sizeof(this->s));
		this->s[0] = 1;
		this->s[1] = x;
		while (this->s[this->s[0]] >= base)
		{
			this->s[this->s[0] + 1] = this->s[this->s[0]] / base;
			this->s[this->s[0]] %= base;
			++this->s[0];
		}
	}
	inline void add(int x)
	{
		if (x || this->s[0])
			this->s[++this->s[0]] = x;
	}
	inline void print()
	{
		printf("%lld", this->s[this->s[0]]);
		for (int i = this->s[0] - 1; i > 0; --i)
			printf("%0*lld", power, this->s[i]);
		printf("\n");
	}
};
bool operator<(const bigint_t &x, const bigint_t &y)
{
	if (x.s[0] < y.s[0])
		return true;
	if (x.s[0] > y.s[0])
		return false;
	for (int i = x.s[0]; i > 0; --i)
		if (x.s[i] != y.s[i])
			return x.s[i] < y.s[i];
	return false;
}
bool operator==(const bigint_t &x, const bigint_t &y)
{
	if (x.s[0] != y.s[0])
		return false;
	for (int i = x.s[0]; i >= 1; --i)
		if (x.s[i] != y.s[i])
			return false;
	return true;
}
bool operator<=(const bigint_t &x, const bigint_t &y)
{
	if (x < y)
		return true;
	if (x == y)
		return true;
	return false;
}
bigint_t operator+(const bigint_t &x, const bigint_t &y)
{
	bigint_t z;
	z.s[0] = max(x.s[0], y.s[0]);
	for (int i = 1; i <= z.s[0]; ++i)
	{
		z.s[i] += (x.s[i] + y.s[i]);
		z.s[i + 1] += (z.s[i] / base);
		z.s[i] %= base;
	}
	while (z.s[z.s[0] + 1])
		++z.s[0];
	return z;
}
bigint_t operator-(const bigint_t &x, const bigint_t &y)
{
	bigint_t z = x;
	for (int i = 1; i <= z.s[0]; ++i)
	{
		z.s[i] -= y.s[i];
		if (z.s[i] < 0)
			z.s[i] += base,
				--z.s[i + 1];
	}
	while (z.s[0] > 0 && !z.s[z.s[0]])
		--z.s[0];
	return z;
}
bigint_t operator*(const bigint_t &x, const bigint_t &y)
{
	bigint_t z;
	z.s[0] = x.s[0] + y.s[0] - 1;
	for (int i = 1; i <= x.s[0]; ++i)
		for (int j = 1; j <= y.s[0]; ++j)
		{
			z.s[i + j - 1] += (x.s[i] * y.s[j]);
			z.s[i + j] += z.s[i + j - 1] / base;
			z.s[i + j - 1] %= base;
		}
	while (z.s[z.s[0] + 1])
		++z.s[0];
	while (!z.s[z.s[0]]) //为了应对乘0
		--z.s[0];
	return z;
}
inline bigint_t cp(const bigint_t &a, int x)
{
	bigint_t t;
	t.s[0] = a.s[0] + x;
	for (int i = 1; i <= a.s[0]; ++i)
		t.s[i + x] = a.s[i];
	return t;
}
inline bigint_t divide(const bigint_t &x, const bigint_t &y, bigint_t &b)
{
	//由于既除又余直接双倍常数=TLE，所以这里偷个懒，一个函数解决两个问题
	bigint_t a;
	a.s[0] = x.s[0] - y.s[0] + 1;
	b = x;
	int st[(int)log2(base) + 5];
	st[0] = 1;
	for (int i = 1; i <= log2(base); ++i)
		st[i] = (st[i - 1] << 1);
	for (int i = a.s[0]; i >= 1; --i)
	{
		bigint_t t = cp(y, i - 1);
		for (int j = log2(base); j >= 0; --j)
			if (t * st[j] <= b)
			{
				a.s[i] = a.s[i] + st[j];
				b = b - (t * st[j]);
			}
	}
	while (a.s[0] > 0 && !a.s[a.s[0]])
		--a.s[0];
	return a;
}
```

## 排序

``std::sort(a+1,a+1+n,cmp);``

### 归并排序求逆序对

可以用树状数组代替。

## 搜索

### BFS（广度优先搜索）

使用``queue``数据结构维护的一种广度优先搜索方法。

#### 双向BFS

当搜索树的**初始状态**和**终止状态**均已知时，可以同时从两个方向BFS，当一个方向的搜索枝搜索到另一个方向的搜索枝时可以直接统计答案，以此加快搜索效率。

#### 同余系BFS

当在搜索树上存在区域性的节点循环、重复的现象，或者可从部分搜索结果推知其他搜索结果时，可以简化为只在其中一个“循环节”上搜索，以此简化搜索树，提高搜索效率。

### DFS（深度优先搜索）

使用``stack``数据结构或者**递归**思想维护的一种深度优先搜索方法。

#### IDDFS（迭代加深搜索）

限定搜索深度（搜索下界）的DFS：当当前搜索深度不能够找到答案时提高搜索深度；当当前搜索深度已经可以搜索到答案时停止搜索，不再提高搜索深度。以此来避免不必要的大量搜索。

### A*（启发式搜索）

使用估价函数$h(x)$辅助剪枝，提高搜索效率的一种搜索方法。

#### IDA*（迭代加深启发式搜索）

在使用估价函数$h(x)$的基础上限定搜索深度$H$的一种搜索方法。

### 记忆化搜索

记录当前搜索节点的答案，若后面再搜索到该节点，可直接返回答案，不必重复搜索。

###剪枝

#### 可行性剪枝

当当前搜索子树已不符合题目要求的条件时，不再向下搜索。

#### 最优性剪枝

当当前搜索子树已可以证明不存在比当前最优解更优的答案时，不再向下搜索。

# 规划

## 动态规划

### 简单动规

-[x] **洛谷P1216** 数字三角形，DP入门题。
-[x] **POJ2533** 最长上升子序列（LIS），朴素$O(N^2)$，可用**二分+栈**优化至$O(N\ log_2N)$。
-[x] **POJ1458** 最长公共子序列（LCS）。
-[x] **HDU1423** 最长公共上升子序列（LCIS）。
-[x] **ZOJ2432** 最长公共上升子序列（LCIS）,要求记录方案（DP路径）并输出。

### 背包

#### 01背包

-[x] **洛谷P2871** 裸01背包。
-[x] **洛谷P2639** 没有价值仅有体积的01背包。
-[x] **洛谷P2925** 体积等于价值，且需要加__可行性剪枝__的01背包。
-[x] **洛谷P1064** 带附件的01背包，注意建立编号索引；当然也可以用树形DP做。

#### 完全背包

-[x] **洛谷P2722** 完全背包。

#### 多重背包

-[x] **洛谷P2347** 多重背包\六重循环暴力。
-[x] **洛谷P1776** 多重背包的__二进制优化__。

#### 混合背包

-[x] **POJ3260\洛谷P2851** 多重背包二进制拆分+完全背包+**抽屉\鸽巢\狄利克雷原理**，注意是求**最小**值的背包。

#### 多维费用背包

-[x] **洛谷P1910** 两个限制条件（两个体积限制）的01背包。

#### 分组背包

-[ ] **ZOJ3164** 超综合背包，**多重背包+分组背包**，值得思考。

#### 树上背包？

#### 同余系背包

#### 衍生问题

##### [TODO:输出方案]

##### [TODO:字典序最小最优解]

##### [TODO:（最优）方案数量]

##### [TODO:第K优解]

### 其他线性DP

- [ ] **TYVJ P1008**
- [ ] **TYVJ P1015**
- [ ] **TYVJ P1124**
- [ ] **TYVJ P1034**

### 非模型DP

-[x] **洛谷P1006** 朴素的四维DP很好想，注意两条路径上不能有重复点，而且最终状态也需要注意。


-[x] **洛谷P1541** 好想也好写，但是状态转移容易出岔子；由于上来就获得第一个位置的价值，所以从初值到转移方程都需要注意：初始值要设为第一个位置的价值；还有状态转移时移动位置要加一，因为上来在第一个格子，而不是第零个。
-[x] **洛谷P1311** 线性预处理上个费用不超过$p$的位置，然后对每种颜色线性线性求出该点及之前有多少同颜色点，之后递推一边就好，算不上真正意义上的DP。
-[x] **洛谷P1081** 倍增DP，不好想，特别注意一个地方！**倍增数组要开到$log_2(N)+1$，不能直接开到$log_2(N)$，例如直接定义了大小为$log_2(N)$的宏时，不能直接把数组开那么大，必须额外开大点！！！不然你连怎么死的都不知道！！！**
-[x] **POJ1191** 暴力4+1维DP，或者爆搜也能过，只要记得方差怎么算就好。
-[ ] **POJ2374**
-[x] **洛谷P1941** 朴素的刷表DP+优化，如果想加速可以拆分成01背包（降）+完全背包（升），另外搜索+剪枝也是可以水过的；**有些优化只能在反向遍历时使用，如果正向遍历+优化TLE，不如改为反向遍历；当然前提是正确性**。
-[x] **洛谷P2679** 超级难想的DP，但是少见的好写，注意初值处理好就行。


### 区间DP

-[x] **洛谷P1514** 好想，但有不少坑。首先易得每个点可以控制的底线范围必定是连续的一段区间，然后就可以记录每个点能到达的区间的极左端点值和极右端点值，最后跑$O(N^2)$区间DP或贪心均可。可用一遍DFS\BFS跑出，顺带着连可行性判定一块跑了；但是切记一定要**记忆化**，否则卡成$O(N^3)$，TLE到怀疑人生。
-[ ] **TYVJ P1055**
-[ ] **TYVJ P1056**

### 树形DP

-[x] **洛谷P1351** 其实不能算是树形DP，因为搜索、贪心都能过。不过在一个狗血的错误上卡了很久：
     **当使用同余原理处理模意义下的减法时，可能出现负数，需要使用(A%P+P)%P处理！！！**
-[ ] **TYVJ P1051**

#### 基环树上DP

-[ ] **BZOJ2878**
-[ ] **BZOJ1791**

#### 仙人掌上DP

-[ ] **BZOJ1023**

### 期望\概率DP

-[x] **洛谷P1850** 状态转移方程贼长，但是不算难想，但是细节极其坑爹：**Floyd初值无限大，自己到自己的初值为零，自环重边注意**，**DP数组初值注意，循环范围注意、答案更新注意**，但但但但是，坑了我最长时间的，是```memset()```**不能用于给double类型数组赋极大值**啊，以后还是改用```fill()```或者```for()```吧，唉……
-[x] **POJ3071** 树上期望DP，但是由于是满二叉树，使用位运算可以巧妙的避开搜索。


### 状态压缩DP

-[x] **洛谷P1052** 线性**模意义**状态压缩DP，注意S=T时的特判，以及模数（最好是LCM）的选择。
-[ ] **POJ1038** **图的最短哈密顿路径**
-[ ] **洛谷P3112**
-[ ] **洛谷P3118**

### 斜率优化DP

-[ ] **BZOJ1010**

### 数位DP

## 线性规划

### 图论模型转化

## 分数规划

### 01分数规划

# 图论

## 最短路

### Dijkstra（优先队列优化）

```cpp
/*
node_t是优先队列内部排序时使用的结构体，dat元素为点编号，len元素为到起始点距离
注意重载node_t结构体的小于号，以便转换默认的大根堆为小根堆。
*/
inline void dijkstra(int c)
{
    memset(dis, 0x3F, sizeof(dis));
    priority_queue<node_t> Q;
    Q.push(node_t(c, dis[c] = 0));
    vis[c] = true;
    while (!Q.empty())
    {
        node_t x = Q.top();
        Q.pop();
        if (x.len != dis[x.dat])
            continue;
        vis[x.dat] = true;
        for (edge_t *k = p[x.dat].nxt; k != NULL; k = k->nxt)
            if (!vis[k->dat] && dis[k->dat] > dis[x.dat] + k->len)
            {
                dis[k->dat] = dis[x.dat] + k->len;
                Q.push(node_t(k->dat, dis[k->dat]));
            }
    }
}
```

### Bellman-Ford

```cpp
//看下面的SPFA就好了
```

### SPFA（SLF+LLL优化）

```cpp
/*
暂时没有LLL优化，因为繁琐且极易负优化。这里使用了手动队列来减小常数，但注意在无法确定数据范围时还是使用STL里的queue来的实在。
*/
inline void SPFA(int c)
{
    memset(dis, 0x3F, sizeof(dis));
    dis[c] = 0LL;
    head = tail = N;
    Q[++head] = c;
    vis[c] = true;
    while (head != tail)
    {
        int x = Q[++tail];
        vis[x] = false;
        for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
        {
            if (dis[k->dat] > dis[x] + k->len)
            {
                dis[k->dat] = dis[x] + k->len;
                if (!vis[k->dat])
                {
                    //SLF优化
                    if (dis[k->dat] < Q[tail + 1])
                        Q[tail--] = k->dat;
                    else
                        Q[++head] = k->dat;
                    vis[k->dat] = true;
                }
            }
        }
    }
}
```

### Floyd

```cpp
/*
注意几个细节：
1、自己到自己的距离为零；
2、不相连两个点初始距离为INF；
3、注意有向图和无向图的区别，下面给出的代码是有向图的。
*/
inline void Floyd()
{
    memset(f, 0x3F, sizeof(f));
    for (int i = 1; i <= n; ++i)
    {
        f[i][i] = 0;
        for (int j = 1; j <= n; ++j)
            scanf("%d", &f[i][j]); //无向图还需加上“f[j][i]=f[i][j];”。
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}
```

### Johnson

```cpp
//TODO
```

### 差分约束

### 次短路

使用Dijkstra\SPFA算法维护最短路$dis$数组的同时，维护一个次短路数组$dis2$即可。

### 第K短路



#### Yen算法

## 树

### 生成树

#### 最小生成树

##### Kruskal

```cpp
//注意最后看看cnt（最小生成树内边数）是否等于n（总顶点数）-1，否则无解。
inline void Kruskal()
{
    for (int i = 1; i <= n; i++)
        father[i] = i, ranking[i] = 1; //初始化父节点和秩数组
    sort(e + 1, e + 1 + m, cmp);       //按边权从小到大排序
    for (int i = 1; i <= m; i++)       //枚举边
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
}
```

##### Prim

```cpp
/*
node_t是优先队列内部排序时使用的结构体，dat元素为点编号，len元素为到起始点距离。
注意重载node_t结构体的小于号，以便转换默认的大根堆为小根堆。
*/
inline int Prim(int start)
{
    int cnt = 0, ans = 0;
    memset(dis, 0x3F, sizeof(dis));
    priority_queue<node_t> Q;
    Q.push(node_t(start, dis[start] = 0));
    while (!Q.empty())
    {
        node_t x = Q.top();
        Q.pop();
        if (dis[x.dat] != x.len)
            continue;
        vis[x.dat] = true;
        ans += x.len, ++cnt;
        for (edge_t *k = p[x.dat].nxt; k != NULL; k = k->nxt)
            //和Dij求最短路唯一的不同：Dij是更新到起始点的距离，Prim是更新到已选节点的距离，特别注意！
            if (!vis[k->dat] && dis[k->dat] > k->len)
            {
                dis[k->dat] = k->len;
                Q.push(node_t(k->dat, dis[k->dat]));
            }
    }
    if (cnt != n)
        return -1;
    return ans;
}
```

#### 次小生成树

先使用Prim算法求出最小生成树权值和$MinST$，然后从每个节点$i$遍历整个最小生成树，定义$F[j]$为从$i$到$j$的路径上**最大边**的权值。遍历图求出$F[j]$的值，然后对于添加每条不在最小生成树中的边$E(i,j)$，新的生成树权值之和就是$MinST+len[E(i,j)]-F[j]$，记录其最小值，则为次小生成树。

当最小生成树和次小生成树的**权值相同**时，说明最小生成树**不**唯一。

#### 第K小生成树

### 树分治

#### 点分治

#### 边分治

### Prufer编码及Cayley定理

### 树的重心及直径

### LCA（最近公共祖先）

-[x] **洛谷P1967** 最大生成树+LCA；注意**别忘了更新倍增的```deep```数组！！！**

#### 倍增

```cpp
//lgN=log2(N)+1，需要事先开好。
int start, st[N][lgN + 2], deep[N]; //一定要比lgN大！后面会从lgN往下循环，如果不开大就会爆炸
bool vis[N];
void DFS(int x, int d)
{ //处理各个节点的深度
    vis[x] = true;
    deep[x] = d;
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
        if (!vis[k->dat])
        {
            st[k->dat][0] = x;
            DFS(k->dat, d + 1);
        }
}
inline void init()
{ //处理倍增数组，需要在求lca之前调用
    st[start][0] = start; //根节点的八辈祖宗都是自己
    DFS(start, 0);
    for (int k = 1; k <= lgN; ++k)
        for (int i = 1; i <= n; ++i)
            st[i][k] = st[st[i][k - 1]][k - 1]; //别把k-1写成k
}
inline int lca(int x, int y)
{
    if (deep[x] < deep[y])
        swap(x, y);
    for (int k = lgN; k >= 0; --k)
        if (deep[st[x][k]] >= deep[y]) //别丢了等号！
            x = st[x][k];
    if (x == y)
        return x;
    for (int k = lgN; k >= 0; --k)
        if (st[x][k] != st[y][k])
        {
            x = st[x][k];
            y = st[y][k];
        }
    return st[x][0]; //不能直接返回x
}
```

#### Tarjan

#### 树链剖分

### 树链剖分及动态树

### DFS序

## 连通性

### 强连通分量

### 双连通分量

### 割点和桥

### 2-SAT

## 网络

### 网络流

#### 最大流-最小割

##### ISAP

##### Dinic（当前弧优化）

##### 预流推进

#### 费用流

##### ZKW费用流

##### 有负费用流

#### 有上下界的网络流

### 二分图

#### 最大匹配

##### 匈牙利算法

```cpp
/*
edge存是否有边；vis存边是否被访问过；link存与当前目标对侧节点连接的本侧节点，-1为没有连接本侧节点。
复杂度O(N*E)
*/
int ans, link[N], vis[N][N], edge[N][N];
bool DFS(int x)
{
    for (int i = 1; i <= n; ++i)
        if (edge[x][i] && !vis[x][i])
        {
            vis[x][i] = true;
            if (link[i] == -1 || DFS(link[i]))
            {
                link[i] = x;
                return true;
            }
        }
    return false;
}
inline void Hungary()
{
    ans = 0;
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; ++i)
        if (DFS(i))
            ++ans;
    printf("%d\n", ans);
}
```

##### Hopcroft-Karp（HK算法）

```cpp
//一种可以在O(Sqrt(N)*E)时间复杂度内求出二分图最大匹配的算法。
```

#### 最优匹配

二分图的最优匹配又称为带权最大匹配，是指在带有权值边的二分图中，求一个匹配使得匹配边上的权值和最大。一般$X$和$Y$集合顶点个数相同，最优匹配也是一个完备匹配，即每个顶点都被匹配。如果个数不相等，可以通过补点加$0$边实现转化。一般使用**KM算法**解决该问题。

##### KM算法

```cpp
//TODO
```

#### 最小顶点覆盖

如果选了一个点就相当于覆盖了以它为端点的所有边，最小顶点覆盖就是**选择最少的点**来**覆盖所有的边**。

最小顶点覆盖在数值上等同于**二分图的最大匹配**。

#### 最大独立集

选出一些顶点使得这些顶点两两不相邻（无边连接），则这些点构成的集合称为独立集。找出一个包含顶点数最多的独立集称为**最大独立集**。

显然，二分图的最大独立集即为**总顶点数-最小顶点覆盖**，也就是**总顶点数-二分图最大匹配数**。

#### 最小路径覆盖

在一个有向图中，找出**最少的路径**，使得这些路径，**经过每一个点，且每一个点只与一条路径相关联**。

由上面可以得出：

1. **一个单独的点是一个路径**。
2. 如果有路径$a,b,c\cdots f,g$；$a$为起点，$g$为终点。那么$a$到$g$的点不在与其他点之间存在有向边。

所以，**最小路径覆盖=总顶点数-二分图最大匹配数**。

证明：

1. 如果匹配数为$0$，那么图中没有边，需要$n$条路径。
2. 如果$a$，$b$之间连一条边，那么匹配数增$1$，需要的路径数会减少$1$，因为$a$，$b$之间只需要一条。

由于此问题经常见于求DAG的最小路径覆盖，所以我们可以把DAG中的每个点拆成两个，分属不同集合；然后，如果有边$E_i=(a,b)$，则从$a$向$b'$连一条有向边；这样，该DAG就转化为了二分图，可以去求最大匹配了。

#### 最大点权覆盖集

转化为网络流解决。

将源点$S$与$u$中连一条权值为$u$的点权的边，汇点$T$和$v$中连一条权值为点权$v$的边，原图中的$u,v$之间的边容量都设为$\infty$，求出最大流就是最大点权覆盖了。

#### 最大点权独立集

最大点权独立集=总点权-最大点权覆盖。

#### 最大团

对于一般图来说，团是一个顶点集合，且由该顶点集合诱导的子图是一个完全图，简单说，就是选出一些顶点，这些顶点**两两之间都有边**。最大团就是使得选出的这个顶点集合**最大**。对于二分图来说，我们默认为左边的所有点之间都有边，右边的所有顶点之间都有边。那么，实际上，我们是要**在左边找到一个顶点子集X，在右边找到一个顶点子集Y，使得X中每个顶点和Y中每个顶点之间都有边**。

有结论：二分图的最大团=**补图**的最大独立集。

补图的定义是：对于二分图中左边一点$x$和右边一点$y$，若$x$和$y$之间有边，那么在补图中没有，否则有。

这个方法很好理解，因为最大独立集是两两不相邻，所以最大独立集的补图两两相邻。

### 方案唯一性

## 拓扑排序

```cpp
/*
ind为点的入度数组，当ind<0时表示已被访问。
*/
queue<int> Q;
inline void toposort()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (ind[j] == 0)
            {
                Q.push(j);
                for (edge_t *k = p[j].nxt; k != NULL; k = k->nxt)
                    --ind[k->dat];
                --ind[j];
                break;
            }
    while (!Q.empty())
    {
        printf("%d ", Q.front());
        Q.pop();
    }
}
```

# 技巧与思想

## 二分

## 三分

##矩阵递推加速

## 位运算

## 离散化

## 图的拆点

## 数列差分和前缀和

## 启发式合并

##哈夫曼编码\哈夫曼树

## CDQ分治\整体二分

##构造

## 可持久化

## 倍增

### RMQ问题

### LCA（最近公共祖先）

## 分块

### 块状链表

## 莫队

### 带修改的莫队

### 树上莫队

## Standard Template Library（STL）