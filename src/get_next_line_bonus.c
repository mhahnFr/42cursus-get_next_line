#include "get_next_line_utils_bonus.h"

t_string_builder	*string_builder_new(void)
{
	t_string_builder	*this;

	this = malloc(sizeof(t_string_builder));
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
		ft_memcpy(str + mover, this->part + this->start_offset, length);
		mover += length;
		this = this->next;
	}
	*(str + mover) = '\0';
	return (str);
}

void	string_builder_cut_nl(t_string_builder **this)
{
	t_string_builder	*tmp;
	t_string_builder	*v_prev;
	t_string_builder	*v_next;

	if (*this != NULL)
	{
		v_next = (*this)->next_fd;
		v_prev = (*this)->previous_fd;
	}
	while (*this != NULL && (*this)->new_line == NULL)
	{
		tmp = (*this)->next;
		free(*this);
		*this = tmp;
	}
	if (*this != NULL)
	{
		(*this)->start_offset = (*this)->new_line - (*this)->part + 1;
		(*this)->new_line = ft_strchr((*this)->part + (*this)->start_offset, '\n');
		(*this)->previous_fd = v_prev;
		(*this)->next_fd = v_next;
	}
	else
	{
		if (v_prev != NULL)
			v_prev->next_fd = v_next;		// ^
		if (v_next != NULL)					// |
			v_next->previous_fd = v_prev;	// | This is too much
		*this = v_next;						// |
	}										// v
}

char	*get_next_line(int fd)
{
	static t_string_builder	*builder = NULL;
	t_string_builder		*current;
	t_string_builder		*tmp;
	char					*line;

	current = builder;
	while (current != NULL)
	{
		if (current->fd == fd)
			break ;
		current = current->next_fd;
	}
	tmp = current;
	line = NULL;
	if (!string_builder_has_new_line(current))
	{
		if (!read_line(&current, fd))
			return (NULL);
	}
	line = string_builder_to_string_nl(current);
	string_builder_cut_nl(&current);
	if (builder == NULL || tmp == builder)
		builder = current;
	else if (current != NULL && tmp == NULL)
	{
		tmp = builder;					// ^
		while (tmp->next_fd != NULL)	// |
			tmp = tmp->next_fd;			// |
		tmp->next_fd = current;			// |This is too much
		current->previous_fd = tmp;		// |
	}									// |
	return (line);						// v
}
