#include "shell.h"

/**
 * add_to_list - Adds an element to the list.
 * @list: The list to add an element to.
 * @str: The string to be added.
 */
void add_to_list(list_t **list, char *str)
{
	list_t *new_node = malloc(sizeof(list_t));

	new_node->str = str;
	new_node->next = *list;
	*list = new_node;
}

/**
 * print_list_string - Prints a list of strings.
 * @list: The list of strings to be printed.
 */
void print_list_string(list_t *list)
{
	while (list)
	{
		printf("%s\n", list->str);
		list = list->next;
	}
}
