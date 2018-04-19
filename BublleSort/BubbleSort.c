#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x[50];

	while(scanf("%d", x) != EOF)
	{
		printf("%d\n", *x);
	}
}