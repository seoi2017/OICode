#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1003
using namespace std;
bool e[N][N], vis[N][N];
int n, m, t, ans, link[N];
bool hunagry(int x)
{
    for (int i = 1; i <= n; i++)
        if (e[x][i] && !vis[x][i])
        {
            vis[x][i] = true;
            if (link[i] == -1 || hunagry(link[i]))
            {
                link[i] = x;
                return true;
            }
        }
    return false;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &t);
    for (int i = 1, x, y; i <= t; i++)
    {
        scanf("%d%d", &x, &y);
        if (x > n || y > m)
            continue;
        e[x][y] = true;
    }
    memset(link, -1, sizeof(link));
    for (int i = 1; i <= n; i++)
        if (hunagry(i))
            ans++;
    printf("%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}