#include "main.h"

/**
 * _myhistory - shows history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: Parameter structure.
 * @str: String alias.
 * Return: 0 (Success), 1 (Error)
 */
int unset_alias(info_t *info, char *str)
{
	char *b, i;
	int ret;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	i = *b;
	*b = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*b = i;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter structure.
 * @str: String alias.
 * Return: 0 (Success), 1 (Error)
 */
int set_alias(info_t *info, char *str)
{
	char *b;

	b = _strchr(str, '=');
	if (!b)
		return (1);
	if (!*++b)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: Alias node.
 * Return: 0 (Success), 1 (Error)
 */
int print_alias(list_t *node)
{
	char *b = NULL, *a = NULL;

	if (node)
	{
		b = _strchr(node->str, '=');
		for (a = node->str; a <= b; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imitates the alias builtin
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *b = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		b = _strchr(info->argv[i], '=');
		if (b)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
