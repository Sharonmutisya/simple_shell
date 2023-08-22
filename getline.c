#include "main.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter structure
 * @buf: address of buffer
 * @len: address of len variable
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		i = getline(buf, &len_p, stdin);
#else
		i = _getline(info, buf, &len_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0'; /* remove trailing newline */
				i--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = i;
				info->cmd_buf = buf;
			}
		}
	}
	return (i);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter structure
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t r, q, len;
	ssize_t i = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	i = input_buf(info, &buf, &len);
	if (i == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		q = r; /* init new iterator to current buf position */
		p = buf + r; /* get pointer for return */

		check_chain(info, buf, &q, r, len);
		while (q < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &q))
				break;
			q++;
		}

		r = q + 1; /* increment past nulled ';'' */
		if (r >= len) /* reached end of buffer? */
		{
			r = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (i); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter structure
 * @buf: buffer
 * @r: size
 * Return: i
 */
ssize_t read_buf(info_t *info, char *buf, size_t *r)
{
	ssize_t i = 0;

	if (*r)
		return (0);
	i = read(info->readfd, buf, READ_BUF_SIZE);
	if (i >= 0)
		*r = i;
	return (i);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t r, len;
	size_t k;
	ssize_t i = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (r == len)
		r = len = 0;

	i = read_buf(info, buf, &len);
	if (i == -1 || (i == 0 && len == 0))
		return (-1);

	c = _strchr(buf + r, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + r, k - r);
	else
		_strncpy(new_p, buf + r, k - r + 1);

	s += k - r;
	r = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: Signal number.
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
