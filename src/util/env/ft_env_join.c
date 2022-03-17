/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:45:13 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:42:57 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_env_join(char *key, char *value)
{
	char	*joined;
	int		i;
	int		j;

	joined = malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value) + 2));
	i = 0;
	j = 0;
	while (key[j])
		joined[i++] = key[j++];
	joined[i++] = '=';
	j = 0;
	while (value[j])
		joined[i++] = value[j++];
	joined[i] = 0;
	return (joined);
}
