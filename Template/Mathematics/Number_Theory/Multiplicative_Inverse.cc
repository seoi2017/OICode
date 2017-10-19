#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define P 20000600
using namespace std;
int n, p, inv[P];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &p);
    printf("%d\n", inv[1] = 1);
    for (int i = 2; i <= n; i++)
    {                                                                     //线性求乘法逆元
        printf("%d\n", inv[i] = (long long)(p - p / i) * inv[p % i] % p); //切记long long，别乘炸了
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}