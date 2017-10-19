#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 128
#define eps 1e-14
using namespace std;
double mt[N][N];
int n;
inline bool Gauss()
{
    int i = 0;
    for (int j = 0; i < n, j < n; j++)
    {
        int index = i;                               //标记为当前行
        for (int k = i; k < n; k++)                  //不要从0开始，会影响之前消好的主元
            if (fabs(mt[k][j] - mt[index][j]) > eps) //绝对值优化，用来减少小数误差
                index = k;                           //...别漏写这句话就行，漏了下面的if就不起效果了
        if (fabs(mt[index][j]) < eps)                //发现自由元
            continue;
        if (index != i)                  //如果有绝对值更大的系数，就交换行
            for (int k = j; k <= n; k++) //从j列开始交换，记得把增广列也交换了
                swap(mt[index][k], mt[i][k]);
        for (int k = 0; k < n; k++)
            if (fabs(mt[k][j]) > eps && k != i)
            {                                //当前行不要消，系数为零的行不用消
                double t = mt[k][j];         //这一项后面会改变，务必事先存储起来，以备使用
                for (int l = j; l <= n; l++) //j列之前的列不用消
                    mt[k][l] = mt[k][l] - t / mt[i][j] * mt[i][l];
            }
        i++;
    }
    for (int k = i; k < n; k++) //判无解
        if (fabs(mt[k][n]) > eps)
            return false;
    if (i < n) //判多解
        return false;
    return true;
}
inline double judge(double x)
{
    if (x == -0.0)
        return 0.0;
    else
        return x;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            scanf("%lf", &mt[i][j]);
    bool can = Gauss();
    if (can)
        for (int i = 0; i < n; i++)
            printf("%.2lf\n", judge(mt[i][n] / mt[i][i]));
    else
        printf("No Solution\n");
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}