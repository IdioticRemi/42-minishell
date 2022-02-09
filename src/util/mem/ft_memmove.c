/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:55:36 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:23:21 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove( void *destination, void *source, size_t size)
{
	const unsigned char	*cast_src;
	unsigned char		*cast_dest;
	unsigned int		i;

	cast_src = (const unsigned char *) source;
	cast_dest = (unsigned char *) destination;
	if (!destination && !source)
		return (NULL);
	i = 0;
	if (cast_src < cast_dest)
	{
		size++;
		while (i < --size)
			cast_dest[size - 1] = cast_src[size - 1];
	}
	else
	{
		while (i < size)
		{
			cast_dest[i] = cast_src[i];
			i++;
		}
	}
	return ((void *)cast_dest);
}
