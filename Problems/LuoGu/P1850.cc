//LuoGu-P1850
//tag:[期望DP（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 2007
#define V 307
using namespace std;
int n, m, v, e;
int c[N], d[N], l[V][V];
double k[N], f[N][N][2];
inline void init()
{
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &k[i]);
    memset(l, 0x3F, sizeof(l));
    for (int i = 1; i <= v; i++)
        l[i][i] = 0;
    for (int i = 1, x, y, z; i <= e; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        l[x][y] = l[y][x] = min(l[x][y], z);
    }
}
inline void floyd()
{
    for (int o = 1; o <= v; o++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                l[i][j] = min(l[i][j], l[i][o] + l[o][j]);
}
inline double dp()
{
    //别在double上用double！！！
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            f[i][j][0] = f[i][j][1] = 1e9;
    //memset(f,0x3f,sizeof(f))->32分
    //memset(f,0x7f,sizeof(f))->100分
    f[1][0][0] = f[1][1][1] = 0.0;
    for (int i = 2; i <= n; i++)
    {
        f[i][0][0] = f[i - 1][0][0] + l[c[i - 1]][c[i]];
        for (int j = 1; j <= min(i, m); j++)
        {
            f[i][j][0] = min(
                f[i - 1][j][0] +
                    l[c[i - 1]][c[i]],
                f[i - 1][j][1] +
                    l[d[i - 1]][c[i]] * k[i - 1] +
                    l[c[i - 1]][c[i]] * (1.0 - k[i - 1])
                );
            f[i][j][1] = min(
                f[i - 1][j - 1][0] +
                    l[c[i - 1]][d[i]] * k[i] +
                    l[c[i - 1]][c[i]] * (1.0 - k[i]),
                f[i - 1][j - 1][1] +
                    l[d[i - 1]][d[i]] * k[i] * k[i - 1] +
                    l[c[i - 1]][d[i]] * k[i] * (1.0 - k[i - 1]) +
                    l[d[i - 1]][c[i]] * (1.0 - k[i]) * k[i - 1] +
                    l[c[i - 1]][c[i]] * (1.0 - k[i]) * (1.0 - k[i - 1])
                );
        }
    }
    double ans = f[n][0][0];
    for (int i = 1; i <= m; i++)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    init();
    floyd();
    printf("%.2lf\n", dp());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}