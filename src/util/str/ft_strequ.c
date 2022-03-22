/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:27:32 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/22 16:44:21 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strequ(char *s1, char *s2)
{
	size_t	i;
	size_t	len;

	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	i = -1;
	len = ft_strlen(s1);
	while (++i < len)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}
