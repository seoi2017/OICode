#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 3
#define P 1000000007
#define MX 2e9 + 7
using namespace std;
typedef long long ll_t;
const int operate_matrix[N][N] = {
    {1, 1, 0},
    {0, 0, 1},
    {1, 0, 0},
};
const int standard_matrix[N][N] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
};
const int original_matrix[N][N] = {
    {1, 1, 1},
    {0, 0, 0},
    {0, 0, 0},
};
struct matrix_t
{
    int mt[N][N];
    matrix_t(int x = 0)
    {
        memset(mt, x, sizeof(mt));
    }
    matrix_t operator*(const matrix_t &x) const
    {
        matrix_t ans;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    ans.mt[i][j] = (ans.mt[i][j] + (ll_t)this->mt[i][k] * x.mt[k][j]) % P;
        return ans;
    }
} c, a;
inline matrix_t expow(matrix_t x, ll_t y)
{
    matrix_t ans;
    memcpy(ans.mt, standard_matrix, sizeof(ans.mt));
    while (y)
    {
        if (y & 1)
            ans = ans * x;
        x = x * x, y >>= 1;
    }
    return ans;
}
int T;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int q; T; T--)
    {
        scanf("%d", &q);
        memcpy(a.mt, original_matrix, sizeof(a.mt));
        memcpy(c.mt, operate_matrix, sizeof(c.mt));
        c = expow(c, max(q - 3, 0));
        a = a * c;
        printf("%d\n", a.mt[0][0]);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}