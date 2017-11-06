#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#define MAX_SUM 16384
using namespace std;
const int base = 100000000;
const int power = 8;
class bigint_t
{
  public:
	long long s[MAX_SUM];
	bigint_t()
	{
		memset(this->s, 0, sizeof(this->s));
	}
	bigint_t(int x)
	{
		*this = x;
	}
	void operator=(const char *str)
	{
		memset(this->s, 0, sizeof(this->s));
		int len = strlen(str);
		this->s[0] = (len + power - 1) / power;
		for (int i = 0, t = 0, w; i < len; w *= 10, ++i)
		{
			if (i % power == 0)
				w = 1, ++t;
			this->s[t] += (w * (str[i] - '0'));
		}
	}
	void operator=(const int x)
	{
		memset(this->s, 0, sizeof(this->s));
		this->s[0] = 1;
		this->s[1] = x;
		while (this->s[this->s[0]] >= base)
		{
			this->s[this->s[0] + 1] = this->s[this->s[0]] / base;
			this->s[this->s[0]] %= base;
			++this->s[0];
		}
	}
	inline void add(int x)
	{
		if (x || this->s[0])
			this->s[++this->s[0]] = x;
	}
	inline void print()
	{
		printf("%lld", this->s[this->s[0]]);
		for (int i = this->s[0] - 1; i > 0; --i)
			printf("%0*lld", power, this->s[i]);
		printf("\n");
	}
};
bool operator<(const bigint_t &x, const bigint_t &y)
{
	if (x.s[0] < y.s[0])
		return true;
	if (x.s[0] > y.s[0])
		return false;
	for (int i = x.s[0]; i > 0; --i)
		if (x.s[i] != y.s[i])
			return x.s[i] < y.s[i];
	return false;
}
bool operator==(const bigint_t &x, const bigint_t &y)
{
	if (x.s[0] != y.s[0])
		return false;
	for (int i = x.s[0]; i >= 1; --i)
		if (x.s[i] != y.s[i])
			return false;
	return true;
}
bool operator<=(const bigint_t &x, const bigint_t &y)
{
	if (x < y)
		return true;
	if (x == y)
		return true;
	return false;
}
bigint_t operator+(const bigint_t &x, const bigint_t &y)
{
	bigint_t z;
	z.s[0] = max(x.s[0], y.s[0]);
	for (int i = 1; i <= z.s[0]; ++i)
	{
		z.s[i] += (x.s[i] + y.s[i]);
		z.s[i + 1] += (z.s[i] / base);
		z.s[i] %= base;
	}
	while (z.s[z.s[0] + 1])
		++z.s[0];
	return z;
}
bigint_t operator-(const bigint_t &x, const bigint_t &y)
{
	bigint_t z = x;
	for (int i = 1; i <= z.s[0]; ++i)
	{
		z.s[i] -= y.s[i];
		if (z.s[i] < 0)
			z.s[i] += base,
				--z.s[i + 1];
	}
	while (z.s[0] > 0 && !z.s[z.s[0]])
		--z.s[0];
	return z;
}
bigint_t operator*(const bigint_t &x, const bigint_t &y)
{
	bigint_t z;
	z.s[0] = x.s[0] + y.s[0] - 1;
	for (int i = 1; i <= x.s[0]; ++i)
		for (int j = 1; j <= y.s[0]; ++j)
		{
			z.s[i + j - 1] += (x.s[i] * y.s[j]);
			z.s[i + j] += z.s[i + j - 1] / base;
			z.s[i + j - 1] %= base;
		}
	while (z.s[z.s[0] + 1])
		++z.s[0];
	while (!z.s[z.s[0]]) //为了应对乘0
		--z.s[0];
	return z;
}
inline bigint_t cp(const bigint_t &a, int x)
{
	bigint_t t;
	t.s[0] = a.s[0] + x;
	for (int i = 1; i <= a.s[0]; ++i)
		t.s[i + x] = a.s[i];
	return t;
}
inline bigint_t divide(const bigint_t &x, const bigint_t &y, bigint_t &b)
{
	//由于既除又余直接双倍常数=TLE，所以这里偷个懒，一个函数解决两个问题
	bigint_t a;
	a.s[0] = x.s[0] - y.s[0] + 1;
	b = x;
	int st[(int)log2(base) + 5];
	st[0] = 1;
	for (int i = 1; i <= log2(base); ++i)
		st[i] = (st[i - 1] << 1);
	for (int i = a.s[0]; i >= 1; --i)
	{
		bigint_t t = cp(y, i - 1);
		for (int j = log2(base); j >= 0; --j)
			if (t * st[j] <= b)
			{
				a.s[i] = a.s[i] + st[j];
				b = b - (t * st[j]);
			}
	}
	while (a.s[0] > 0 && !a.s[a.s[0]])
		--a.s[0];
	return a;
}
char a[MAX_SUM], b[MAX_SUM];
bigint_t A, B, ans, mod;
int main()
{
#ifdef LOCAL
	freopen("io/in", "r", stdin);
	freopen("io/out", "w", stdout);
#endif
	scanf("%s", a);
	reverse(a, a + strlen(a));
	scanf("%s", b);
	reverse(b, b + strlen(b));
	A = a, B = b;
	ans = A + B;
	ans.print();
	if (B < A)
		ans = A - B;
	else
		ans = B - A,
		printf("-");
	ans.print();
	ans = A * B;
	ans.print();
	ans = divide(A, B, mod);
	ans.print();
	mod.print();
#ifdef LOCAL
	fclose(stdin);
	fclose(stdout);
#endif
	return 0;
}