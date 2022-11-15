#include "shell.h"

/**
 * create_envlist - creates a linked list with all environment
 * variables in the extern environ variable
 * Return: head of created list
 */

env_t *create_envlist(void)
{
	env_t *head;
	int i;

	head = NULL;
	for (i = 0; environ[i] != NULL; i++)
		add_env(&head, environ[i]);
	return (head);
}

/**
 * add_env - adds another environmental variable to the end
 * of the environemental variable linked list
 * @head: head of the linked list
 * @str: environmental variable val to store
 * Return: the address of the new element, on fail, program exits
 */
env_t *add_env(env_t **head, char *str)
{
	env_t *newnode;
	env_t *temp;

	newnode = safe_malloc(sizeof(env_t));
	newnode->val = _strdup(str);
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (newnode);
}

/**
 * remove_env - removes an environmental variable
 * @head: pointer to the head of the linked list
 * @index: the nth node to delete
 */
void remove_env(env_t **head, int index)
{
	env_t *temp;
	env_t *d_node;
	int i;
	/*DEBUG: Shouldn't this just remove env by name, why by index?*/
	i = 0;
	temp = *head;
	if (index == 0)
	{
		*head = (*head)->next;
		_free(temp->val);
		_free(temp);
	}
	else
	{
		while (i < index - 1)
		{
			temp = temp->next;
			i++;
		}
		d_node = temp->next;
		temp->next = d_node->next;
		_free(d_node);
	}
}

/**
 * print_env - prints all environmental variables and its values
 * @head: head pointer to the linked list
 */
void print_env(env_t *head)
{
	env_t *temp;

	temp = head;
	while (temp != NULL)
	{
		_write(temp->val);
		_write("\n");
		temp = temp->next;
	}
}

/**
 * update_env - updates an environemental variable
 * @envp: linked list of environemental variables
 * @name: the name of variable to update;
 * @val: the val to update env with
 * @bufsize: buffer size
 */
void update_env(env_t *envp, char *name, char *val, int bufsize)
{
	char *rep;
	env_t *temp;

	rep = safe_malloc(sizeof(char) * bufsize);
	_memset(rep, '\0', bufsize);
	_strcat(rep, name);
	_strcat(rep, val);
	for (temp = envp; temp != NULL; temp = temp->next)
	{
		if (_strstr(temp->val, name) != NULL && temp->val[0] == name[0])
		{
			temp->val = rep;
			break;
		}
	}
}
