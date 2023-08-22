#include "main.h"

/**
 **_strncpy - copies string
 *@dest: Destination string to be copied to.
 *@src: Source string.
 *@n: amount of characters to be copied.
 *Return: Concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int r, q;
	char *d = dest;

	r = 0;
	while (src[r] != '\0' && r < n - 1)
	{
		dest[r] = src[r];
		r++;
	}
	if (r < n)
	{
		q = r;
		while (q < n)
		{
			dest[q] = '\0';
			q++;
		}
	}
	return (d);
}

/**
 **_strncat - concatenates two strings
 *@dest: First string.
 *@src: Second string.
 *@n: Amount of bytes to be maximally used.
 *Return: Concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int r, q;
	char *d = dest;

	r = 0;
	q = 0;
	while (dest[r] != '\0')
		r++;
	while (src[q] != '\0' && q < n)
	{
		dest[r] = src[q];
		r++;
		q++;
	}
	if (q < n)
		dest[r] = '\0';
	return (d);
}

/**
 **_strchr - locates a character in a string
 *@s: String to be parsed.
 *@c: Character to look for.
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
