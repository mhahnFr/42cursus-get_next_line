#include "get_next_line_bonus.h"
#include "get_next_line_utils_bonus.h"

t_string_builder	*string_builder_new(void)
{
	t_string_builder	*this;

	this = malloc(sizeof(t_string_builder) + BUFFER_SIZE * sizeof(char));
	if (this != NULL)
	{
		this->new_line = NULL;
		this->next = NULL;
		this->start_offset = 0;
		this->string_length = 0;
		this->next_fd = NULL;
		this->previous_fd = NULL;
	}
	return (this);
}

size_t	string_builder_size_nl(t_string_builder *this)
{
	size_t	size;

	size = 0;
	while (this != NULL)
	{
		if (this->new_line == NULL)
			size += (this->string_length - this->start_offset);
		else
		{
			size += (this->new_line - this->part) - this->start_offset + 1;
			break ;
		}
		this = this->next;
	}
	return (size);
}

char	*string_builder_to_string_nl(t_string_builder *this)
{
	char	*str;
	size_t	mover;
	size_t	length;

	str = NULL;
	length = string_builder_size_nl(this);
	if (length == 0)
		return (NULL);
	str = malloc(length + 1);
	if (str == NULL)
		return (NULL);
	mover = 0;
	while (this != NULL)
	{
		if (this->new_line == NULL)
			length = (this->string_length - this->start_offset);
		else
			length = (this->new_line - this->part) - this->start_offset + 1;
		gnl_memcpy(str + mover, this->part + this->start_offset, length);
		mover += length;
		this = this->next;
	}
	*(str + mover) = '\0';
	return (str);
}

void	string_builder_cut_nl(t_string_builder **s)
{
	t_string_builder	*tmp;
	t_string_builder	*prev;
	t_string_builder	*next;

	if (*s != NULL)
	{
		prev = (*s)->previous_fd;
		next = (*s)->next_fd;
	}
	while (*s != NULL && (*s)->new_line == NULL)
	{
		tmp = (*s)->next;
		free(*s);
		*s = tmp;
	}
	if (*s != NULL)
	{
		(*s)->start_offset = (*s)->new_line - (*s)->part + 1;
		(*s)->new_line = gnl_memchr((*s)->part + (*s)->start_offset, '\n', (*s)->string_length - (*s)->start_offset);
		(*s)->previous_fd = prev;
		(*s)->next_fd = next;
	}
	else
	{
		if (prev != NULL)
			prev->next_fd = next;
		if (next != NULL)
			next->previous_fd = prev;
		*s = next;
	}
}

char	*get_next_line(int fd)
{
	static t_string_builder	*builder = NULL;
	t_string_builder		*current;
	t_string_builder		*tmp;
	char					*line;

	current = builder;
	if (!string_builder_get_has_new_line(&current, &tmp, fd)
		&& !read_line(&current, fd))
		return (NULL);
	line = string_builder_to_string_nl(current);
	string_builder_cut_nl(&current);
	if (builder == NULL || tmp == builder)
		builder = current;
	else if (current != NULL && tmp == NULL)
	{
		tmp = builder;
		while (tmp->next_fd != NULL)
			tmp = tmp->next_fd;
		tmp->next_fd = current;
		current->previous_fd = tmp;
	}
	return (line);
}
