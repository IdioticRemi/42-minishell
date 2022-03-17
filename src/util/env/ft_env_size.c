/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:44:47 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:44:49 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_env_size(t_env **env)
{
	t_env	*tmp;
	size_t	size;

	if (!env || !*env)
		return (0);
	size = 0;
	tmp = *env;
	while (tmp && ++size)
		tmp = tmp->next;
	return (size);
}
