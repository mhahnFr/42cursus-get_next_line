#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
/*
 * A string builder part. It includes the actual string part of the size of
 * the specified buffer size plus one for the null terminator. There is also
 * the pointer to the newline character in the string part, if a newline
 * character is present. The offset indicates at which position to start.
 * Of course, there is also a pointer to the next part.
 */
typedef struct s_string_builder {
	char					part[BUFFER_SIZE + 1];
	char					*new_line;
	size_t					start_offset;
	struct s_string_builder	*next;
}	t_string_builder;

/*
 * Returns the next line of the file indicated by the given file descriptor.
 * If nothing else to read is left, or an error occures, null is returned.
 */
char	*get_next_line(int fd);
#endif