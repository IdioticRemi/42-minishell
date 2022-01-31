# include "../include/header.h"

char	*ft_strdup(char *src)
{
	char	*cped;
	int	i;

	cped = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (cped == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		cped[i] = src[i];
		i++;
	}
	cped[i] = '\0';
	return (cped);
}