/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:58:08 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:23:55 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	index;
	size_t	index_result;

	if (!s)
		return (NULL);
	index_result = 0;
	index = 0;
	result = malloc(ft_min(len, ft_strlen(s)) + 1);
	if (result == NULL)
		return (NULL);
	while (s[index] != '\0')
	{
		if (index >= start && index_result < len)
		{
			result[index_result] = s[index];
			index_result++;
		}
		index++;
	}
	result[index_result] = '\0';
	return (result);
}
