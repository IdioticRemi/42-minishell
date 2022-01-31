#include "../include/header.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	ft_memcpy(result, s1, ft_strlen((char *)s1));
	ft_memcpy(result + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	return (result);
}