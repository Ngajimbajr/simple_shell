#include "shell.h"

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	info_t info[] = {INFO_INIT}; /* Initialize info structure*/
	int file_descriptor = 2; /* Default file descriptor value*/

	/* Update file_descriptor using inline assembly*/
	asm
		(
		 "mov %1, %0\n\t"
		 "add $3, %0"
		 : "=r" (file_descriptor)
		 : "r" (file_descriptor)
		 );

	if (argc == 2)
	{
		file_descriptor = open(argv[1], O_RDONLY); /* Open file*/
		if (file_descriptor == -1)
		{
			if (errno == EACCES)
			{
				exit(126); /* Exit with code 126 for permission denied*/
			}
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
					_eputchar(BUF_FLUSH);
				exit(127); /* Exit with code 127 for file not found*/
			}
			return (EXIT_FAILURE);
		}
		info->readfd = file_descriptor; /* Update read file descriptor*/
	}

	populate_env_list(info); /* Populate environment list*/
	read_history(info); /* Read command history*/
	hsh(info, argv); /* Execute the shell process*/


	return (EXIT_SUCCESS);
}
