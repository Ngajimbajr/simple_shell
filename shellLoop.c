#include "shell.h"

/**
 * @brief Main shell loop.
 *
 * This function contains the main loop of the shell.
 * It reads user input, processes built-in commands,
 * and executes external commands.
 *
 * @param info Pointer to the shell information structure.
 * @param av   Argument vector from main().
 *
 * @return Returns 0 on success, 1 on error, or an error code.
 */
int hsh(info_t *info, char **av) {
    ssize_t read_status = 0;
    int builtin_return = 0;

    while (read_status != -1 && builtin_return != -2) {
        clear_info(info);

        if (interactive(info))
            _puts("$ ");

        _eputchar(BUF_FLUSH);
        read_status = get_input(info);

        if (read_status != -1) {
            set_info(info, av);
            builtin_return = find_builtin(info);

            if (builtin_return == -1)
                find_cmd(info);
        } else if (interactive(info)) {
            _putchar('\n');
        }

        free_info(info, 0);
    }

    write_history(info);
    free_info(info, 1);

    if (!interactive(info) && info->status)
        exit(info->status);

    if (builtin_return == -2) {
        if (info->err_num == -1)
            exit(info->status);

        exit(info->err_num);
    }

    return builtin_return;
}

/**
 * @brief Find a built-in command and execute it.
 *
 * This function searches for a built-in command in the
 * command list and executes the corresponding function.
 *
 * @param info Pointer to the shell information structure.
 *
 * @return Returns -1 if the built-in command is not found,
 *         0 if the built-in command executed successfully,
 *         1 if the built-in command was found but not successful,
 *         or -2 if a built-in command signals an exit().
 */
int find_builtin(info_t *info) {
    int i, built_in_ret = -1;
    
    builtin_table builtintbl[] = {
        {"exit", _myexit},
        {"env", _myenv},
        {"help", _myhelp},
        {"history", _myhistory},
        {"setenv", _mysetenv},
        {"unsetenv", _myunsetenv},
        {"cd", _mycd},
        {"alias", _myalias},
        {NULL, NULL}
    };

    for (i = 0; builtintbl[i].type; i++) {
        if (_strcmp(info->argv[0], builtintbl[i].type) == 0) {
            info->line_count++;
            built_in_ret = builtintbl[i].func(info);
            break;
        }
    }

    return built_in_ret;
}

/**
 * @brief Find and execute an external command in the PATH.
 *
 * This function searches for an external command in the PATH
 * environment variable and executes it if found. If not found,
 * it prints an error message.
 *
 * @param info Pointer to the shell information structure.
 *
 * @return Void.
 */
void find_cmd(info_t *info) {
    char *path = NULL;
    int i, k;

    info->path = info->argv[0];

    if (info->linecount_flag == 1) {
        info->line_count++;
        info->linecount_flag = 0;
    }

    for (i = 0, k = 0; info->arg[i]; i++) {
        if (!is_delim(info->arg[i], " \t\n")) {
            k++;
        }
    }

    if (!k) {
        return;
    }

    path = find_path(info, _getenv(info, "PATH="), info->argv[0]);

    if (path) {
        info->path = path;
        fork_cmd(info);
    } else {
        if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') &&
            is_cmd(info, info->argv[0])) {
            fork_cmd(info);
        } else if (*(info->arg) != '\n') {
            info->status = 127;
            print_error(info, "not found\n");
        }
    }
}

/**
 * @brief Fork a child process to execute a command.
 *
 * This function forks a child process and uses the
 * execve function to execute the command in the child.
 * It handles errors and prints error messages if needed.
 *
 * @param info Pointer to the shell information structure.
 *
 * @return Void.
 */
void fork_cmd(info_t *info) {
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == -1) {
        /* TODO: Implement error handling function */
        perror("Error:");
        return;
    }

    if (child_pid == 0) {
        if (execve(info->path, info->argv, get_environ(info)) == -1) {
            free_info(info, 1);

            if (errno == EACCES)
                exit(126);

            exit(1);
        }

        /* TODO: Implement error handling function */
    } else {
        wait(&(info->status));

        if (WIFEXITED(info->status)) {
            info->status = WEXITSTATUS(info->status);

            if (info->status == 126)
                print_error(info, "Permission denied\n");
        }
    }
}
