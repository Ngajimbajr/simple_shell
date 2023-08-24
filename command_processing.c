#include "shell.h"

/**
 * is_chain - Checks if the current character in buffer is a chaining delimiter
 *
 * This function examines the buffer to determine whether the current character
 * and its following character form a chain delimiter.
 *
 * @info: The parameter struct containing information.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * Return: 1 if a chain delimiter is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0; /* Replace semicolon with null*/
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * check_chain - Checks whether to continue chaining based on the last status.
 *
 * This function checks whether chaining should continue based on the last
 * command's exit status and modifies the buffer accordingly.
 *
 * @info: The parameter struct containing information.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 * Return: void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias -  Replaces aliases in the tokenized string.
 *
 * This function iterates through a list of aliases and replaces the tokenized
 * string with the corresponding alias if found.
 *
 * @info: The parameter struct containing information.
 * Return: 1 if an alias is replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
		{
			return (0);
		}
		p = _strdup(p + 1);
		if (!p)
		{
			return (0);
		}
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 *
 * This function iterates through the tokenized string and replaces variables
 * with their corresponding values if found.
 *
 * @info :The parameter struct containing information.
 * Return: 1 if a variable is replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]), _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - Replaces a string with a new value.
 *
 * Function replaces an old string with a new string value, freeing the old
 * memory allocation in the process.
 *
 * @old: Address of the old string.
 * @new: New string value.
 * Return: 1 if the string is replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
