
#include <stdio.h>
#include "stack.h"
#include "string.h"
#include "stdlib.h"

int main()
{
	int n;

	Stack *s = stack_construct();

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		char command[20];
		scanf("\n%s", command);

		if (strcmp(command, "PUSH") == 0)
		{
			char *val = calloc(20, sizeof(char));
			scanf("%s\n", val);
			stack_push(s, val);
		}

		if (strcmp(command, "POP") == 0)
		{
			char *val = stack_pop(s);
			printf("%s\n", val);
		}
	}

	stack_destroy(s);

	return 0;
}