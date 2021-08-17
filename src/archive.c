/*
 * This file includes some older functions, that are worth to be saved.
 */

#include "get_next_line_utils.h"
#define BUFFER_SIZE 42

/*
 * Creates a string with the whole content of the given string builder.
 */
char	*string_builder_to_string(t_string_builder *this)
{
	char	*str;
	size_t	mover;
	size_t	length;

	str = malloc(string_builder_size(this) + 1);
	mover = 0;
	while (this != NULL)
	{
		if (this->next != NULL)
			length = BUFFER_SIZE;
		else
			length = ft_strlen(this->part);
		ft_memcpy(str + mover, this->part, length);
		mover += length;
		this = this->next;
	}
	*(str + mover) = '\0';
}

/*
 * Old version of the GNL. Works completely, it is just a little bit slow.
 */
char	*get_next_line1(int fd)
{
	static char	*rest = NULL;
	char		*tmp;
	char		*buffer;
	char		*nl;
	int			ret;

	ret = 1;
	nl = NULL;
	buffer = NULL;
	if (rest != NULL)
		nl = ft_strchr(rest, '\n');
	if (nl == NULL)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (NULL);
	}
	while (nl == NULL)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		buffer[ret] = '\0';
		if (ret <= -1)
		{
			free(buffer);
			if (rest != NULL)
				free(rest);
			return (NULL);
		}
		else if (ret == 0)
			break ;
		if (rest != NULL)
		{
			tmp = ft_strdup(rest);
			free(rest);
			rest = NULL;
			rest = ft_strjoin(tmp, buffer);
			free(tmp);
			tmp = NULL;
		}
		else
			rest = ft_strdup(buffer);
		nl = ft_strchr(rest, '\n');
	}
	if (buffer != NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	if (nl != NULL)
	{
		tmp = ft_substr(rest, 0, nl - rest + 1);
		buffer = ft_strdup(rest);
		free(rest);
		rest = NULL;
		nl = ft_strchr(buffer, '\n');
		rest = ft_substr(buffer, nl - buffer + 1, ft_strlen(buffer));
		free(buffer);
		buffer = NULL;
	}
	else if (ret == 0 && (rest == NULL || ft_strlen(rest) == 0))
	{
		tmp = NULL;
		if (rest != NULL)
		{
			free(rest);
			rest = NULL;
		}
	}
	else
	{
		tmp = ft_strdup(rest);
		free(rest);
		rest = NULL;
	}
	return (tmp);
}
