#include "main.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the sring to input
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_delim(str[j], d) && (is_delim(str[j + 1], d) || !str[j + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, i = 0; i < numwords; i++)
	{
		while (is_delim(str[j], d))
			j++;
		k = 0;
		while (!is_delim(str[j + k], d) && str[j + k])
			k++;
		s[i] = malloc((k + 1) * sizeof(char));
		if (!s[i])
		{
			for (k = 0; k < i; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[i][m] = str[j++];
		s[i][m] = 0;
	}
	s[i] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the string to input
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (j = 0; str[j] != '\0'; j++)
		if ((str[j] != d && str[j + 1] == d) ||
		    (str[j] != d && !str[j + 1]) || str[j + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, i = 0; i < numwords; i++)
	{
		while (str[j] == d && str[j] != d)
			j++;
		k = 0;
		while (str[j + k] != d && str[j + k] && str[j + k] != d)
			k++;
		s[i] = malloc((k + 1) * sizeof(char));
		if (!s[i])
		{
			for (k = 0; k < i; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[i][m] = str[j++];
		s[i][m] = 0;
	}
	s[i] = NULL;
	return (s);
}
