#include "shell.h"

/**
 * initializeInfo - Function to initialize an info_t struct
 *
 * @info:struct address.
 * Return:void
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setupInfo - Sets up information structure.
 * @info: Pointer to info_t structure to be initialized.
 * @av: Array of command line arguments.
 */
void setupInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];

	if (info->arg)
	{
		info->argv = printString(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = allocateMemory(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		substituteAliases(info);
		substituteVariables(info);
	}
}

/**
 * releaseInfo - Releases all allocated resources.
 * @info: Pointer to info_t structure to be released.
 * @all: Whether to free all resources (1) or not (0).
 */
void releaseInfo(info_t *info, int freeAll)
{
	freeMemory(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (freeAll)
	{
		if (!info->commandBuffer)
			freeMemory(info->arg);

		if (info->environ)
			free_list(&(info->environ));

		if (info->commandHistory)
			free_list(&(info->commandHistory));

		if (info->aliasList)
			free_list(&(info->aliasList));

		freeMemory(info->environVariables);
		info->environVariables = NULL;

		freeMemoryArray((void **)info->commandBuffer);

		if (info->readFileDescriptor > 2)
		{
				close(info->readFileDescriptor);

				printChar(BUF_FLUSH);
		}
	}
}
