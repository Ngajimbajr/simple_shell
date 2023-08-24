#include "shell.h"

/**
 * printCurrentEnvironment - Prints the current environment information.
 * @info: A pointer to the info_t structure containing environment information.
 *
 * Return: Always 0.
 */
int printCurrentEnvironment(info_t *info)
{
	printListStrings(info->env);
	return (0);
}

/**
 * getEnvironmentVariable - Retrieves value of specific environment variable.
 * @info: A pointer to the info_t structure containing environment information.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: If the variable is found,returns its value; otherwise, returns NULL.
 */
char *getEnvironmentVariable(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *value;

	while (node)
	{
		value = startsWith(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}
	return (NULL);
}

/**
 * setOrModifyEnvironmentVariable - Sets or modifies an environment variable.
 * @info: A pointer to the info_t structure containing environment information.
 *
 * Return: 0 on success, 1 on failure.
 */
int setOrModifyEnvironmentVariable(info_t *info)
{
	if (info->argc != 3)
	{
		printError("Incorrect number of arguments\n");
		return (1);
	}
	if (setEnvironmentVariable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironmentVariable - Unsets specified environment variables.
 * @info: A pointer to the info_t structure containing environment information.
 *
 * Return: 0 on success, 1 on failure.
 */
int unsetEnvironmentVariable(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		printError("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unsetVariable(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - Populates the environment list.
 * @info: A pointer to the info_t structure containing environment information.
 *
 * Return: Always 0.
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeToEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
