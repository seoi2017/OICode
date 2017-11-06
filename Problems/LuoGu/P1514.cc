//LuoGu-P1514
//tag:[动态规划（规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 512
using namespace std;
const int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m, h[N][N], f[N], l[N][N], r[N][N], ans;
bool vis[N][N], can = true;
void DFS(int x, int y)
{
    vis[x][y] = true;
    for (int i = 0, nx, ny; i < 4; i++)
    {
        nx = x + dir[i][0], ny = y + dir[i][1];
        if (nx <= 0 || ny <= 0 || nx > n || ny > m)
            continue;
        if (h[nx][ny] >= h[x][y])
            continue;
        if (!vis[nx][ny])
            DFS(nx, ny);
        l[x][y] = min(l[x][y], l[nx][ny]);
        r[x][y] = max(r[x][y], r[nx][ny]);
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%d", &h[i][j]);
    memset(l, 0x3F, sizeof l);
    memset(r, 0x00, sizeof r);
    for (int i = 1; i <= m; i++)
        l[n][i] = r[n][i] = i;
    for (int i = 1; i <= m; i++)
        DFS(1, i);
    for (int i = 1; i <= m; i++)
        if (!vis[n][i])
        {
            can = false;
            ans++;
        }
    if (!can)
    {
        printf("0\n%d\n", ans);
        goto end;
    }
    printf("1\n");
    memset(f, 0x3F, sizeof(f));
    f[0] = 0;
    for (int i = 1; i <= m; i++)
    {
        if (!l[i] || !r[i])
            continue;
        for (int j = l[1][i]; j <= r[1][i]; j++)
            f[j] = min(f[j], f[l[1][i] - 1] + 1);
    }
    printf("%d\n", f[m]);
end:
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}