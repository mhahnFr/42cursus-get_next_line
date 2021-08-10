#include <stdlib.h>

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

char	*ft_strchr(const char *s, int c)
{
	int	size;
	int	counter;

	size = ft_strlen(s);
	counter = 0;
	while (counter <= size)
	{
		if (s[counter] == (char) c)
			return ((char *) &s[counter]);
		counter++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

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
