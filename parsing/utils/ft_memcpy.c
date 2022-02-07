#include "../include/header.h"

void	*ft_memcpy( void *destination, const void *source, size_t size )
{
	const unsigned char	*cast_src;
	unsigned char		*cast_dest;
	int					i;

	cast_src = (const unsigned char *) source;
	cast_dest = (unsigned char *) destination;
	i = 0;
	if ((size == 0) || (destination == source))
		return (destination);
	while ((size_t)i < size)
	{
		cast_dest[i] = cast_src[i];
		i++;
	}
	return ((void *)cast_dest);
}