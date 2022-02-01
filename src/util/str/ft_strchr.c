/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:23:55 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/01 12:26:45 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	s_len;

	i = -1;
	s_len = ft_strlen(s);
	if (!c)
		return ((char *)s + s_len);
	while (++i < s_len)
		if (s[i] == (char) c)
			return ((char *)s + i);
	return (0);
}

size_t	ft_strichr(char *s, int c)
{
	size_t	i;
	size_t	s_len;

	i = -1;
	s_len = ft_strlen(s);
	if (!c)
		return (s_len);
	while (++i < s_len)
		if (s[i] == (char) c)
			return (i);
	return (-1);
}
