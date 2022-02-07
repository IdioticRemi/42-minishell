# include "../include/header.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((char)s1[i] == (char)s2[i] && n > i)
	{
		if ((char)s1[i] == '\0' && (char)s2[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}