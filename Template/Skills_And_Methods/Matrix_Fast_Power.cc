#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 128
#define P 1000000007
using namespace std;
typedef long long ll_t;
int n;
ll_t k;
struct matrix_t
{
    ll_t mt[N][N];
    matrix_t(int x = 0)
    {
        memset(mt, x, sizeof(mt));
    }
    matrix_t operator*(const matrix_t &x) const
    {
        matrix_t ans;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    ans.mt[i][j] = (ans.mt[i][j] + this->mt[i][k] * x.mt[k][j]) % P; //先ik后kj，千万别写反！
        return ans;
    }
} matrix;
template <typename T>
T expow(T x, ll_t m)
{
    T ans = x;
    m--; //一次方不用算
    //由于没有用单位矩阵，所以不能算零次方
    while (m)
    {
        if (m & 1)
            ans = ans * x;
        x = x * x, m >>= 1;
    }
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%lld", &matrix.mt[i][j]);
    matrix = expow(matrix, k);
    for (int i = 1; i <= n; i++, printf("\n"))
        for (int j = 1; j <= n; j++)
            printf("%d ", matrix.mt[i][j]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}