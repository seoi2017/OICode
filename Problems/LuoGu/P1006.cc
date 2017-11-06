//LuoGu-P1006
//tag:[动态规划（规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 51
using namespace std;
int m, n, a[N][N], f[N][N][N][N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= m; k++)
                for (int l = 1; l <= n; l++)
                    if (i != k || j != l)
                        f[i][j][k][l] = max(max(f[i - 1][j][k - 1][l], f[i][j - 1][k - 1][l]), max(f[i - 1][j][k][l - 1], f[i][j - 1][k][l - 1])) + a[i][j] + a[k][l];
    printf("%d\n", f[m][n - 1][m - 1][n]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}