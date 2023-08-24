#include "shell.h"

/**
 * count_nodes - Counts the number of nodes in a linked list.
 * @head: Pointer to the first node.
 *
 * Returns: Number of nodes in the list.
 */
size_t count_nodes(const list_t *head) {
    size_t count = 0;

    while (head) {
        head = head->next;
        count++;
    }

    return count;
}

/**
 * list_to_string_array - Converts a linked list to an array of strings.
 * @head: Pointer to the first node.
 *
 * Returns: Array of strings.
 */
char **list_to_string_array(list_t *head) {
    list_t *node = head;
    size_t num_nodes = count_nodes(head);
    char **strings;
    char *string;

    if (!head || num_nodes == 0) {
        return NULL;
    }

    strings = (char **)malloc(sizeof(char *) * (num_nodes + 1));
    if (!strings) {
        return NULL;
    }

    for (size_t i = 0; node; node = node->next, i++) {
        string = (char *)malloc(strlen(node->str) + 1);
        if (!string) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return NULL;
        }

        strcpy(string, node->str);
        strings[i] = string;
    }

    strings[num_nodes] = NULL;
    return strings;
}

/**
 * print_linked_list - Prints elements of a linked list.
 * @head: Pointer to the first node.
 *
 * Returns: Number of nodes in the list.
 */
size_t print_linked_list(const list_t *head) {
    size_t count = 0;

    while (head) {
        print_number_as_string(head->num, 10, 0);
        putchar(':');
        putchar(' ');
        puts(head->str ? head->str : "(nil)");
        head = head->next;
        count++;
    }

    return count;
}

/**
 * find_node_with_prefix - Finds a node whose string starts with a prefix.
 * @node: Pointer to the list head.
 * @prefix: Prefix to match.
 * @c: The next character after prefix to match.
 *
 * Returns: Node that matches the condition or NULL.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c) {
    char *start = NULL;

    while (node) {
        start = starts_with(node->str, prefix);
        if (start && (c == -1 || *start == c)) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Returns: Index of the node or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node) {
    size_t index = 0;

    while (head) {
        if (head == node) {
            return index;
        }
        head = head->next;
        index++;
    }

    return -1;
}
