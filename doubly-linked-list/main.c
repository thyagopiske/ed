
#include <stdio.h>
#include "queue.h"
#include "string.h"
#include "stdlib.h"

int main()
{
	int n;

	Queue *s = queue_construct();

	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		char command[20];
		scanf("\n%s", command);

		if (strcmp(command, "ENQUEUE") == 0)
		{
			char *val = calloc(20, sizeof(char));
			scanf("%s\n", val);
			queue_push(s, val);
		}

		if (strcmp(command, "DEQUEUE") == 0)
		{
			char *val = queue_pop(s);
			printf("%s\n", val);
		}
	}

	queue_destroy(s);

	return 0;
}