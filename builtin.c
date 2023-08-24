#include "shell.h"

/**
 * _myexit - Exits the program with a specified status.
 * @info: A pointer to the info_t struct.
 *
 * Return: 1 if an error occurred, -2 if successful.
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		/*Check for an exit argument*/
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - Change the current working directory.
 * @info: A pointer to the info_t struct.
 *
 * Return: Always returns 0.
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
	}

	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
		{
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		}
		else
		{
			chdir_ret = chdir(dir);
		}
	}
	else if(_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * _myhelp - Display help information.
 * @info: A pointer to the info_t struct.
 *
 * Return: None.
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");

	if (0)
	{
		_puts(*arg_array);/* Temp unused workaround*/
	}
}
