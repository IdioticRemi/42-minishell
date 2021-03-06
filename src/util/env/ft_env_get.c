/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:06:46 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 14:05:37 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strequ(key, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
