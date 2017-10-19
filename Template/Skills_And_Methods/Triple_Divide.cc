#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 16
using namespace std;
const double eps = 1e-8;
int n;
double l, r, a[N];
inline double judge(double x)
{
    double ans = a[0];
    for (int i = 1; i <= n; i++)
        ans = (ans * x) + a[i]; //从高到低表示第i次项系数，可以这样写
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%lf%lf", &n, &l, &r);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &a[i]);
    while (l < r)
    {
        if (r - l < eps)
        {
            printf("%.5lf\n", r);
            break;
        }
        double nl = l + (r - l) / 3, nr = r - (r - l) / 3;
        double cl = judge(nl), cr = judge(nr);
        if (cl > cr)
            r = nr;
        else
            l = nl;
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}