#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <stdbool.h>

#include "get_next_line.h"
#include "../Libft/src/libft.h"

/*
 * Allocates a new string builder part. All values are set to null. Returns the
 * newly allocated, empty string builder part.
 */
t_string_builder	*string_builder_new(void)
{
	t_string_builder	*this;

	this = malloc(sizeof(t_string_builder));
	this->new_line = NULL;
	this->next = NULL;
	this->start_offset = 0;
	return (this);
}

/*
 * Calculates the string length of the string builder. Counting stops at the
 * first newline character encountered. It does not search for newline
 * characters in the strings, it only checks for the newline variable in the
 * struct. If no newline is encountered, simply returns the length until the
 * null terminator in the last string builder part. Returns the calculated
 * size.
 */
size_t	string_builder_size_nl(t_string_builder *this)
{
	size_t	size;

	size = 0;
	while (this != NULL)
	{
		if (this->new_line == NULL)
		{
			if (this->next != NULL)
				size += (BUFFER_SIZE - this->start_offset);
			else
				size += ft_strlen(this->part + this->start_offset);
		}
		else
		{
			size += (this->new_line - this->part) - this->start_offset + 1;
			break ;
		}
		this = this->next;
	}
	return (size);
}

/*
 * Creates a string consisting of all string builder parts until the newline
 * character or the end is reached. Returns a newly allocated and null
 * terminated string.
 */
char	*string_builder_to_string_nl(t_string_builder *this)
{
	char	*str;
	size_t	mover;
	size_t	length;

	str = malloc(string_builder_size_nl(this) + 1);
	mover = 0;
	while (this != NULL)
	{
		if (this->new_line == NULL)
		{
			if (this->next != NULL)
				length = BUFFER_SIZE - this->start_offset;
			else
				length = ft_strlen(this->part + this->start_offset);
		}
		else
			length = (this->new_line - this->part) - this->start_offset + 1;
		ft_memcpy(str + mover, this->part + this->start_offset, length);
		mover += length;
		this = this->next;
	}
	*(str + mover) = '\0';
	return (str);
}

/*
 * Appends the given string builder part to the given string builder. If the
 * string builder is null, the given appendix takes the first place in the
 * string builder.
 */
void	string_builder_append(t_string_builder **this,
							t_string_builder *appendix)
{
	t_string_builder	*tmp;

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

/*
 * Deletes the leading string builder parts before the part with the newline
 * character set. Sets then the offset to the position of the newline
 * character. Returns the cutted string builder.
 */
t_string_builder	*string_builder_cut_nl(t_string_builder *this)
{
	t_string_builder	*tmp;

	while (this != NULL && this->new_line == NULL)
	{
		tmp = this->next;
		free(this);
		this = tmp;
	}
	if (this != NULL)
	{
		this->start_offset = this->new_line - this->part + 1;
		this->new_line = ft_strchr(this->part + this->start_offset, '\n');
	}
	return (this);
}

/*
 * Checks each node if the newline character is set. Stops checking at the
 * first encountered newline. Returns true, if a newline is found within the
 * given string builder, false otherwise or if null is given.
 */
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

/*
 * Reads one line from the file determined by the given file descriptor into
 * the given string builder. Depending on the specified buffer size, some
 * characters could follow after the newline character.
 */
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
		tmp->part[ret] = '\0';
		tmp->new_line = ft_strchr(tmp->part, '\n');
		newline = tmp->new_line;
		string_builder_append(builder, tmp);
	}
	return (true);
}

char	*get_next_line(int fd)
{
	static t_string_builder	*builder = NULL;
	char					*line;

	line = NULL;
	if (!string_builder_has_new_line(builder))
	{
		if (!read_line(&builder, fd))
			return (NULL);
	}
	line = string_builder_to_string_nl(builder);
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = NULL;
	}
	builder = string_builder_cut_nl(builder);
	return (line);
}
