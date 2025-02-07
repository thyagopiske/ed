#include "stdio.h"
#include "stdlib.h"
#include "forward_list.h"
#include "string.h"

void print_data(data_type data)
{
	printf("%d\n", (int)data);
}

int main()
{
	int n;
	scanf("%d", &n);

	ForwardList *list = forward_list_construct();
	int val;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &val);
		forward_list_push_front(list, val);
	}

	bool houveTrocas = true;
	while (houveTrocas)
	{
		houveTrocas = false;
		Node *node = list->head;
		Node *aux;
		Node *prev = NULL;
		while (node != NULL && node->next != NULL)
		{
			if (node->value > node->next->value)
			{
				aux = node->next;

				node->next = node->next->next;
				aux->next = node;

				if (prev != NULL)
				{
					prev->next = aux;
				}
				

				if (list->head == node)
				{
					list->head = aux;
				}

				houveTrocas = true;
			}
			
			prev = node;
			node = node->next;
		}
	}

	forward_list_print(list, print_data);
	forward_list_destroy(list);

	return 0;
}