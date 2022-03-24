/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 20:21:50 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/23 20:21:55 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_key(char *key)
{
	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*(++key))
		if (!ft_isalpha(*key) && !ft_isdigit(*key) && *key != '_')
			return (0);
	return (1);
}
