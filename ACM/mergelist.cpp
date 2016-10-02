#include <stdio.h>

int Fibonacci(int n);

int main(void)
{
	int n;

	puts("Please input a integer:");
	scanf("%d", &n);
	/*for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\n", i,Fibonacci(i));
	}*/
	printf("%d\n", Fibonacci(n));
	return 0;
}

int Fibonacci(int n)
{
	if (n < 0)
		puts("Error!\n");
	else if (n <= 1)
	{
		return 1;
	}
	else
		return Fibonacci(n-1)+ Fibonacci(n-2);
}
