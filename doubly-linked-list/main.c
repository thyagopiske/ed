
#include <stdio.h>
#include "deque.h"
#include "string.h"

int main()
{
	int n, val;

	Deque *f = deque_construct();

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		char command[20];
		scanf("\n%s", command);

		if (strcmp(command, "PUSH_FRONT") == 0)
		{
			scanf("%d", &val);
			deque_push_front(f, val);
		}

		if (strcmp(command, "PUSH_BACK") == 0)
		{
			scanf("%d", &val);
			deque_push_back(f, val);
		}

		if (strcmp(command, "POP_FRONT") == 0)
		{
			val = deque_pop_front(f);
			printf("%d\n", val);
		}

		if (strcmp(command, "POP_BACK") == 0)
		{
			val = deque_pop_back(f);
			printf("%d\n", val);
		}
	}

	deque_destroy(f);

	return 0;
}