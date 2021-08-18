#ifndef GET_NEXT_LINE_UTILS_BONUS_H
#define GET_NEXT_LINE_UTILS_BONUS_H

#include <stdlib.h>
#include <stdbool.h>

/*
 * A string builder part. It includes the actual string part of the size of
 * the specified buffer size plus one for the null terminator. There is also
 * the pointer to the newline character in the string part, if a newline
 * character is present. The offset indicates at which position to start. The
 * length of the string can also be stored. The file descriptor from which the
 * string was read takes also part of the struct. There are two pointers: One
 * to the next element, and optionally one to the list for the next file
 * descriptor.
 */
typedef struct s_string_builder {
	/* The string which makes part of the builder. */
	char					part[BUFFER_SIZE + 1];

	/*
	 * A pointer to the newline character in the part, or null if no newline
	 * character is present.
	 */
	char					*new_line;

	/* The file descriptor that was used to read this part. */
	int						fd;

	/* The offset at which to start using the string part. */
	size_t					start_offset;

	/*
	 * The length of the string part. It is less than the buffer size, if these
	 * are the last characters in the file.
	 */
	size_t					string_length;

	/*
	 * A pointer to the first part of the string builder used by the previous
	 * file descriptor.
	 */
	struct s_string_builder	*previous_fd;

	/*
	 * A pointer to the first part of the string builder used by the next file
	 * descriptor.
	 */
	struct s_string_builder	*next_fd;

	/* A pointer to the next part of this string builder. */
	struct s_string_builder	*next;
}	t_string_builder;

/*
 * Iterates through the given buffer at most the given length amount of bytes.
 * Compares the content as unsigned characters. Returns a pointer to the
 * occurance of the given character, or null, if the given buffer does not
 * contain the given character within the given length.
 */
void				*ft_memchr(const void *s, int c, size_t n);

/*
 * Calculates the length of the given string. It returns
 * the count of characters before the first null terminator
 * occurs. Counting starts at zero.
 */
size_t				ft_strlen(const char *s);

/*
 * Copies the given amount of bytes from the given source to
 * the given destination. It does not handle possible memory
 * overlays. Use ft_memmove if an overlay of the memory could
 * be possible. Returns the given destination.
 */
void				*ft_memcpy(void *dst, const void *src, size_t n);

/*
 * Reads one line from the file determined by the given file descriptor into
 * the given string builder. Depending on the specified buffer size, some
 * characters could follow after the newline character.
 */
bool				read_line(t_string_builder **builder, int fd);

/*
 * Allocates a new string builder part. All values are set to null. Returns the
 * newly allocated, empty string builder part.
 */
t_string_builder	*string_builder_new(void);

/*
 * Calculates the string length of the string builder. Counting stops at the
 * first newline character encountered. It does not search for newline
 * characters in the strings, it only checks for the newline variable in the
 * struct. If no newline is encountered, simply returns the length until the
 * null terminator in the last string builder part. Returns the calculated
 * size.
 */
size_t				string_builder_size_nl(t_string_builder *thiss);

/*
 * Creates a string consisting of all string builder parts until the newline
 * character or the end is reached. Returns a newly allocated and null
 * terminated string.
 */
char				*string_builder_to_string_nl(t_string_builder *thiss);

/*
 * Deletes the leading string builder parts before the part with the newline
 * character set. Sets then the offset to the position of the newline
 * character. Returns the cutted string builder.
 */
void				string_builder_cut_nl(t_string_builder **thiss);

/*
 * First, searches for the appopriate node for the given file descriptor.
 * Stores the result of that operation in the struct pointed to by original.
 * Finally, checks each node if the newline character is set. Stops checking at the
 * first encountered newline. Returns true, if a newline is found within the
 * given string builder, false otherwise or if null is found.
 */
bool				string_builder_get_has_new_line(t_string_builder **thiss,
						t_string_builder **original,
						int fd);

/*
 * Appends the given string builder part to the given string builder. If the
 * string builder is null, the given appendix takes the first place in the
 * string builder. The function also sets the length information of the
 * given appendix using the given length. Also, it adds the null terminator to
 * the string of the given appendix.
 */
void				string_builder_append(
						t_string_builder **thiss,
						t_string_builder *appendix,
						int length);
#endif