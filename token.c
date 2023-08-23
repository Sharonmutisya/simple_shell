#include "main.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: String to input.
 * @d: Delimeter string.
 * Return: pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int r, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (j = 0; str[j] != '\0'; j++)
		if (!is_del(str[j], d) && (is_del(str[j + 1], d) || !str[j + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0, r = 0; r < numwords; r++)
	{
		while (is_del(str[j], d))
			j++;
		k = 0;
		while (!is_del(str[j + k], d) && str[j + k])
			k++;
		s[r] = malloc((k + 1) * sizeof(char));
		if (!s[r])
		{
			for (k = 0; k < r; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[r][m] = str[j++];
		s[r][m] = 0;
	}
	s[r] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: String to input.
 * @d: delimeter.
 * Return: pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int r, j, k, m, numwords = 0;
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
	for (j = 0, r = 0; r < numwords; r++)
	{
		while (str[j] == d && str[j] != d)
			j++;
		k = 0;
		while (str[j + k] != d && str[j + k] && str[j + k] != d)
			k++;
		s[r] = malloc((k + 1) * sizeof(char));
		if (!s[r])
		{
			for (k = 0; k < r; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[r][m] = str[j++];
		s[r][m] = 0;
	}
	s[r] = NULL;
	return (s);
}
