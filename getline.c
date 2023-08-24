#include "shell.h"

// This function buffers chained commands.
// It reads input and processes it line by line, detecting command chains.
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    // If there's nothing left in the buffer, fill it.
    if (!*len) {
        // Free the old buffer, if any.
        free(*buf);
        *buf = NULL;

        // Set up signal handler for Ctrl+C.
        signal(SIGINT, sigintHandler);

        // Read input line from stdin.
#if USE_GETLINE
        r = getline(buf, &len_p, stdin);
#else
        r = _getline(info, buf, &len_p);
#endif

        if (r > 0) {
            // Remove trailing newline.
            if ((*buf)[r - 1] == '\n') {
                (*buf)[r - 1] = '\0';
                r--;
            }

            // Process the input line.
            info->linecount_flag = 1;
            remove_comments(*buf);
            build_history_list(info, *buf, info->histcount++);

            // Check if it's a command chain.
            {
                *len = r;
                info->cmd_buf = buf;
            }
        }
    }
    return r;
}

// This function gets input from the user.
// It handles command chaining and returns the processed input.
ssize_t get_input(info_t *info)
{
    static char *buf; // Command chain buffer.
    static size_t i, j, len;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUF_FLUSH); // Flush buffer.
    r = input_buf(info, &buf, &len);
    if (r == -1) // EOF
        return -1;

    if (len) {
        j = i;
        p = buf + i;

        check_chain(info, buf, &j, i, len);

        while (j < len) {
            if (is_chain(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= len) {
            i = len = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return _strlen(p);
    }

    *buf_p = buf;
    return r;
}

// This function reads a buffer from a file descriptor.
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;

    r = read(info->readfd, buf, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;

    return r;
}

// This function gets the next line of input from STDIN.
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return p ? (free(p), -1) : -1;

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}

// Signal handler for Ctrl+C.
void sigintHandler(__attribute__((unused)) int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
