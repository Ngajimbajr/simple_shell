#include "shell.h"

/**
 * displayHistory - Display the history list,showing command with a line number
 * The line numbers start at 0.
 *
 * @info: Structure containing potential arguments.
 * Return: Always returns 0.
 */
int displayHistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unsetAlias - Unset an alias by providing the alias string.
 *
 * @info: Parameter struct.
 * @str: The alias string.
 * Return: Returns 0 on success, 1 on error.
 */
int unsetAlias(info_t *info, char *str)
{
	char *equalSign, originalChar;
	int ret;

	equalSign = _strchr(str, '=');
	if (!equalSign)
		return (1);
	originalChar = *equalSign;
	*equalSign = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*equalSign = originalChar;
	return (ret);
}

/**
 * setAlias - Set an alias using the provided alias string.
 *
 * @info: Parameter struct.
 * @str: The alias string.
 * Return: Returns 0 on success, 1 on error.
 */
int setAlias(info_t *info, char *str)
{
	char *equalSign;

	equalSign = _strchr(str, '=');
	if (!equalSign)
		return (1);
	if (!*++equalSign)
		return (unsetAlias(info, str));

	unsetAlias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * printAlias - Print an alias string.
 *
 * @node: The alias node to be printed.
 * Return: Returns 0 on success, 1 on error.
 */
int printAlias(list_t *node)
{
	char *equalSignPosition = NULL, *aliasPart = NULL;

	if (node)
	{
		equalSignPosition = _strchr(node->str, '=');
		for (aliasPart = node->str; aliasPart <= equalSignPosition; aliasPart++)
			_putchar(*aliasPart);
		_putchar('\'');
		_puts(equalSignPosition + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manageAliases - Mimics the alias builtin (man alias).
 *
 * @info: Structure containing potential arguments.
 * Return: Always returns 0.
 */
int manageAliases(info_t *info)
{
	int i = 0;
	char *equalSignPosition = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			printAlias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		equalSignPosition = _strchr(info->argv[i], '=');
		if (equalSignPosition)
			setAlias(info, info->argv[i]);
		else
			printAlias(node_starts_with(info->alias, info->argv[i], '='));
	}
}

