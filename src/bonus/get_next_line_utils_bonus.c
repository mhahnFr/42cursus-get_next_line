#include <unistd.h>

#include "get_next_line_utils_bonus.h"

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	size_t	counter;

	counter = 0;
	if ((src != NULL || dst != NULL) && n > 0)
	{
		while (counter < n)
		{
			((char *) dst)[counter] = ((char *) src)[counter];
			counter++;
		}
	}
	return (dst);
}

void	*gnl_memchr(const void *s, int c, size_t n)
{
	size_t	counter;

	counter = 0;
	while (counter < n)
	{
		if (((unsigned char *) s)[counter] == (unsigned char) c)
			return ((void *) &s[counter]);
		counter++;
	}
	return (NULL);
}

bool	read_line(t_string_builder **builder, int fd)
{
	t_string_builder	*tmp;
	char				*newline;
	int					ret;

	newline = NULL;
	while (newline == NULL)
	{
		tmp = string_builder_new();
		if (tmp == NULL)
			return (false);
		ret = read(fd, tmp->part, BUFFER_SIZE);
		if (ret <= 0)
		{
			free(tmp);
			if (ret < 0)
				return (false);
			break ;
		}
		tmp->new_line = gnl_memchr(tmp->part, '\n', ret);
		tmp->fd = fd;
		newline = tmp->new_line;
		string_builder_append(builder, tmp, ret);
	}
	return (true);
}

void	string_builder_append(t_string_builder **this,
							t_string_builder *appendix,
							int length)
{
	t_string_builder	*tmp;

	appendix->string_length = length;
	if (*this == NULL)
	{
		*this = appendix;
		return ;
	}
	tmp = *this;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = appendix;
}

bool	string_builder_get_has_new_line(t_string_builder **this,
										t_string_builder **original,
										int fd)
{
	t_string_builder	*tmp;

	while (*this != NULL)
	{
		if ((*this)->fd == fd)
			break ;
		*this = (*this)->next_fd;
	}
	*original = *this;
	tmp = *this;
	while (tmp != NULL)
	{
		if (tmp->new_line != NULL)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
