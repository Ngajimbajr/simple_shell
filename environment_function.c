#include "shell.h"

// Function to print the current environment
// Arguments:
//   - info: Structure containing potential arguments. Used to maintain
//            constant function prototype.
// Returns: Always 0
int printCurrentEnvironment(info_t *info)
{
    printListStrings(info->env);
    return 0;
}

// Function to get the value of an environment variable
// Arguments:
//   - info: Structure containing potential arguments. Used to maintain
//   - name: Name of the environment variable
// Returns: The value of the environment variable, or NULL if not found
char *getEnvironmentVariable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value;

    while (node)
    {
        value = startsWith(node->str, name);
        if (value && *value)
            return value;
        node = node->next;
    }
    return NULL;
}

// Function to set or modify an environment variable
// Arguments:
//   - info: Structure containing potential arguments. Used to maintain
// Returns: Always 0
int setOrModifyEnvironmentVariable(info_t *info)
{
    if (info->argc != 3)
    {
        printError("Incorrect number of arguments\n");
        return 1;
    }
    if (setEnvironmentVariable(info, info->argv[1], info->argv[2]))
        return 0;
    return 1;
}

// Function to unset an environment variable
// Arguments:
//   - info: Structure containing potential arguments. Used to maintain
// Returns: Always 0
int unsetEnvironmentVariable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        printError("Too few arguments.\n");
        return 1;
    }
    for (i = 1; i <= info->argc; i++)
        unsetVariable(info, info->argv[i]);

    return 0;
}

// Function to populate the environment linked list
// Arguments:
//   - info: Structure containing potential arguments. Used to maintain
// Returns: Always 0
int populateEnvironmentList(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        addNodeToEnd(&node, environ[i], 0);
    info->env = node;
    return 0;
}
