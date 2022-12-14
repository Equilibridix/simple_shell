#include "shell.h"

/**
 * _memcpy - copies num bytes form the memory area src
 * to memory area dest
 * @src: source code to copy.
 * @dest: destination to copy to.
 * @num: how many bytes to copy.
 * Return: dest;
 */

char *_memcpy(char *dest, char *src, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 *_memset - sets first num bytes of the memory area
 * @s: array to set
 * @b: what to set it to
 * @num: first num bytes
 * Return: s
 */

char *_memset(char *s, char b, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
	{
		s[i] = b;
	}
	return (s);
}

/**
 * _strcat - appends strings
 * @dest: destination to append
 * @src: what to append
 * Return: pointer to dest
 */

char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	/*i++;*/
	dest[i] = '\0';
	return (dest);
}

/**
 * _strncat - concatenates one string (number of byte given)
 * to another
 * @dest: where to concatenate
 * @src: string to concatenate
 * @num: how many bytes to
 * Return: dest
 */

char *_strncat(char *dest, char *src, int num)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
	{
	}
	j = 0;
	while (j < num && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strstr - finds the first occurence of the substring needle
 * in the string haystack
 * @haystack: string to search
 * @needle: string to find
 * Return: pointer to the beginning of the located substring
 */

char *_strstr(char *haystack, char *needle)
{

	while (*haystack != '\0')
	{
		char *beginning = haystack;
		char *pattern = needle;

		while (*pattern == *haystack && *pattern != '\0'
		       && *haystack != '\0')
		{
			haystack++;
			pattern++;
		}
		if (*pattern == '\0')
			return (beginning);
		haystack = beginning + 1;
	}
	return (NULL);
}
