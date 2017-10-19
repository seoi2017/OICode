#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10007
using namespace std;
int father[N], n, m, ranking[N];
inline int find_father(int x)
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
        father[i] = i, ranking[i] = 1;
    for (int i = 1, x, y, z; i <= m; i++)
    {
        scanf("%d%d%d", &z, &x, &y);
        if (z == 1)
        {
            x = find_father(x);
            y = find_father(y);
            if (x == y)
                continue;
            if (ranking[x] < ranking[y])
                swap(x, y);
            father[y] = x;
            ranking[x] += ranking[y];
        }
        else
        {
            x = find_father(x);
            y = find_father(y);
            x == y ? printf("Y\n") : printf("N\n");
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}