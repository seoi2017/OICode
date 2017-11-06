//LuoGu-P1541
//tag:[动态规划（规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 128
using namespace std;
int n, m, a[N << 2], c[N >> 4], f[N >> 1][N >> 1][N >> 1][N >> 1];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1, x; i <= m; i++)
        scanf("%d", &x), c[x]++;
    f[0][0][0][0] = a[1]; //初始值十分重要
    for (int i = 0; i <= c[1]; i++)
        for (int j = 0; j <= c[2]; j++)
            for (int k = 0; k <= c[3]; k++)
                for (int l = 0; l <= c[4]; l++)
                {
                    int nxt = 1 + i * 1 + j * 2 + k * 3 + l * 4; //开始的那个1十分重要
                    if (i)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i - 1][j][k][l] + a[nxt]);
                    if (j)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j - 1][k][l] + a[nxt]);
                    if (k)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k - 1][l] + a[nxt]);
                    if (l)
                        f[i][j][k][l] = max(f[i][j][k][l], f[i][j][k][l - 1] + a[nxt]);
                }
    printf("%d\n", f[c[1]][c[2]][c[3]][c[4]]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}