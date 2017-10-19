#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define N 131072 //最大区间长度
#define M 17     //log2(M)，由于不能用函数返回值定义数组大小，故提前算出
using namespace std;
int n, m, st[N][M]; //ST表数组
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &st[i][0]);                                          //区间中第i位的数其实是从第i位起2^0范围内的最大值
    for (int i = 1; i <= M; i++)                                         //倍增最多M次即可覆盖可能的最大区间
        for (int j = 1; j + (1 << i) - 1 <= n; j++)                      //如果倍增一次不超过区间总长度
            st[j][i] = max(st[j][i - 1], st[j + (1 << (i - 1))][i - 1]); //更新区间最大值
    for (int i = 1, x, y, k; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        k = log2(y - x + 1);                                    //覆盖区间[x,y]至少需要从x开始2^(k+1)长度
        printf("%d\n", max(st[x][k], st[y - (1 << k) + 1][k])); //取区间最大值
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
}