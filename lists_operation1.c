#include "shell.h"

/**
 * count_nodes - Counts the number of nodes in a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes in the linked list.
 */
size_t count_nodes(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * list_to_string_array - Convert linked list of strings to an array of string.
 * @head: A pointer to the head of the linked list.
 *
 * Return: A dynamically allocated array of strings, or NULL on failure.
 */
char **list_to_string_array(list_t *head)
{
	list_t *node = head;
	size_t num_nodes = count_nodes(head);
	char **strings;
	char *string;

	if (!head || num_nodes == 0)
	{
		return (NULL);
	}

	strings = (char **)malloc(sizeof(char *) * (num_nodes + 1));
	if (!strings)
	{
		return (NULL);
	}

	for (size_t i = 0; node; node = node->next, i++)
	{
		string = (char *)malloc(strlen(node->str) + 1);
		if (!string)
		{
			for (size_t j = 0; j < i; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}

		strcpy(string, node->str);
		strings[i] = string;
	}

	strings[num_nodes] = NULL;
	return (strings);
}

/**
 * print_linked_list - Prints the elements of a linked list.
 * @head: A pointer to the head of the linked list.
 *
 * Return: The number of nodes printed.
 */
size_t print_linked_list(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		print_number_as_string(head->num, 10, 0);
		putchar(':');
		putchar(' ');
		puts(head->str ? head->str : "(nil)");
		head = head->next;
		count++;
	}

	return (count);
}

/**
 * find_node_with_prefix - Finds a node in linked list with specific prefix.
 * @node: A pointer to the head of the linked list.
 * @prefix: The prefix to search for.
 * @c: The character to check after the prefix, or -1 to ignore.
 *
 * Return: A pointer to the node containing the desired prefix and character,
 *         or NULL if no such node is found.
 */
list_t *find_node_with_prefix(list_t *node, char *prefix, char c)
{
	char *start = NULL;

	while (node)
	{
		start = starts_with(node->str, prefix);
		if (start && (c == -1 || *start == c))
		{
			return (node);
		}
		node = node->next;
	}

	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list.
 * @head: A pointer to the head of the linked list.
 * @node: A pointer to the node whose index is to be found.
 *
 * Return: The index of the node in the linked list, or -1 if not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
		{
			return (index);
		}
		head = head->next;
		index++;
	}

	return (-1);
}
