#include <stdio.h>
#include <stdbool.h>

//输出数据
void Show(int *a, int ct);

//a中是否存在和b相同的元素
bool IsSame(int *a, int b, int ct);

int main(void)
{
	int m, n;
	int i;
	int a[200];
	int b[100];

	while (scanf("%d", &m) != EOF)
	{
		for (i = 0; i < m; i++)
			scanf("%d", &a[i]);
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d", &b[i]);
		Show(a, m);
		Show(b, n);
		for (i = 0; i < n; i++)
		{
			if (!IsSame(a, b[i], m))
			{
				a[m] = b[i];
				++m;
				Show(a, m);
			}
			else
				Show(a, m);
		}
		putchar('\n');
	}
}

void Show(int *a, int ct)
{
	for (int i = 0; i < ct; i++)
	{
		if (i)
			printf(" %d", a[i]);
		else
			printf("%d", a[i]);
	}
	putchar('\n');
}

bool IsSame(int *a, int b, int m)
{
	for (int i = 0; i < m; i++)
	{
		if (b == a[i])
			return true;
	}
	return false;
}
