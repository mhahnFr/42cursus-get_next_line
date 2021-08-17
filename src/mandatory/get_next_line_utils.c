#include <unistd.h>

#include "get_next_line_utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

char	*ft_strchr(const char *s, int c)
{
	int	counter;

	counter = 0;
	while (s[counter] != '\0')
	{
		if (s[counter] == (char) c)
			return ((char *) &s[counter]);
		counter++;
	}
	if (s[counter] == (char) c)
		return ((char *) &s[counter]);
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
		ret = read(fd, tmp->part, BUFFER_SIZE);
		if (ret <= -1)
		{
			free(tmp);
			return (false);
		}
		else if (ret == 0)
		{
			free(tmp);
			break ;
		}
		tmp->new_line = ft_strchr(tmp->part, '\n');
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
	appendix->part[length] = '\0';
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

bool	string_builder_has_new_line(t_string_builder *this)
{
	while (this != NULL)
	{
		if (this->new_line != NULL)
			return (true);
		this = this->next;
	}
	return (false);
}
