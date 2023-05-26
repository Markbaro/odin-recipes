#include "simple_shell.h"

/**
  * _strlen - reads no of characters in str
  * @str: string to be counted
  * Return: len of str
  */
size_t _strlen(const char *str)
{
	size_t len;

	for (len = 0; str[len] != '\0'; len++)
	{
	}
	return (len);
}

/**
  * _strcmp - compares length of various strings
  * @str1: string to be compaes
  * @str2: string to be compared
  * Return: diff of len of strings
  */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 < *str2)
		{
			return (-1);
		}
		else if (*str1 > *str2)
		{
			return (1);
		}
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/**
  * _strdup - duplicates a string
  * @str : the string to duplicate
  * Return: duplicated str
  */

char *_strdup(const char *str)
{
	size_t length = _strlen(str) + 1;
	char *new_str = (char *)malloc(length * sizeof(char));

	if (new_str != NULL)
	{
		return (NULL);
	}
	_strcpy(new_str, str);
	return (new_str);
}

/**
 * _strchr - searches for the first occurrence of a character in a string
 * @str: the string to search
 * @ch: the character to find
 * Return: pointer to occurance of char
 */
char *_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strcpy - copies the string
 * @dest: the destination buffer
 * @src: the source string
 * Return: pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
	char *original_dest = dest;

	while (*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (original_dest);
}
/**
 * _strcat - concatenates two strings
 * @dest: Pinter the dest of the copied string,char
 * @src: const character pointer the source of string
 * Return: dest
 */

char *_strcat(const char *str1, const char *str2)
{
	char *result;
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	size_t i;

	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));

	if (result == NULL)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	_strcpy(result, str1);

	for (i = 0; i < len2; i++)
	{
		result[len1 + i] = str2[i];
	}
	result[len1 + len2] = '\0';
	return (result);
}
