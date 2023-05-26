#include "shell.h"

/**
 * addAliasEnd - This adds a node to the end of a alias_t
 * linked list.
 * @head: A pointer to the head of the alias_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 * Return: on error return NULL else return a
 * pointer to the new node
 */
alias_t *addAliasEnd(alias_t **head, char *name, char *value)
{
	alias_t *newNode = malloc(sizeof(alias_t));
	alias_t *last;

	if (!newNode)
		return (NULL);

	newNode->next = NULL;
	newNode->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!newNode->name)
	{
		free(newNode);
		return (NULL);
	}
	newNode->value = value;
	_strcpy(newNode->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * addNodeEnd - This adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The dir path for new node to contain.
 * Return: on error return NULL else return a
 * pointer to the new node
 */
list_t *addNodeEnd(list_t **head, char *dir)
{
	list_t *newNode = malloc(sizeof(list_t));
	list_t *last;

	if (!newNode)
		return (NULL);

	newNode->dir = dir;
	newNode->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * freeAliasList - Thsi frees an alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void freeAliasList(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

/**
 * freeList - Thsi frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void freeList(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
