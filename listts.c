#include "main.h"

/**
 * list_len - determine length of linked list
 * @h: first node pointer
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t j = 0;

	while (h)
	{
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: first node pointer
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t r = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !r)
		return (NULL);
	strs = malloc(sizeof(char *) * (r + 1));
	if (!strs)
		return (NULL);
	for (r = 0; node; node = node->next, r++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < r; j++)
				free(strs[r]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[r] = str;
	}
	strs[r] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of list_t linked list
 * @h: first node pointer
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t r = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		r++;
	}
	return (r);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: List head pointer.
 * @prefix: String to match.
 * @c: Next character after prefix to match.
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: list head pointer
 * @node: node pointer
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t r = 0;

	while (head)
	{
		if (head == node)
			return (r);
		head = head->next;
		r++;
	}
	return (-1);
}
