//1324: 算法2 - 2：有序线性表的有序合并
#include <stdio.h>

int main(void)
{
	int a[100];
	int b[100];
	int c[200];
	int m, n;
	int i, j, k;

	while (scanf("%d", &m) != EOF)
	{
		for (i = 0; i < m; i++)
			scanf("%d", &a[i]);
		scanf("%d", &n);
		for (j = 0; j < n; j++)
			scanf("%d", &b[j]);

		i = j = k =0;
		while (i < m && j < n)
		{
			if (a[i] < b[j])
			{
				c[k] = a[i];
				++k;
				++i;
			}
			else
			{
				c[k] = b[j];
				++k;
				++j;
			}
		}

		while (i < m)
		{
			c[k] = a[i];
			++k;
			++i;
		}
		while (j < n)
		{
			c[k] = b[j];
			++k;
			++j;
		}

		//输出
		for (i = 0; i < k; i++)
		{
			if (i)
				printf(" %d", c[i]);
			else
				printf("%d", c[i]);
		}
		putchar('\n');
	}
	return 0;
}


