/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:06:46 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/23 20:14:50 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_freeone_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	ft_del_env(t_env **env, char *key)
{
	t_env	*before;
	t_env	*tmp;

	before = NULL;
	tmp = *env;
	while (tmp && !ft_strequ(tmp->key, key))
	{
		before = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	if (!before)
	{
		*env = tmp->next;
		ft_freeone_env(tmp);
		return ;
	}
	before->next = tmp->next;
	ft_freeone_env(tmp);
}
