#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
/*
 * Returns the next line of the file indicated by the given file descriptor.
 * If nothing else to read is left, or an error occures, null is returned.
 */
char				*get_next_line(int fd);
#endif