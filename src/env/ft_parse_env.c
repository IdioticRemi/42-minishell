/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:52:17 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:27:28 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_parse_env(char **_env)
{
	t_env	*env;
	char	**tmp;
	int		i;

	env = NULL;
	i = -1;
	while (_env[++i])
	{
		tmp = ft_split(_env[i], '=');
		if (!tmp || !tmp[0])
			return (NULL);
		if (tmp[1])
			ft_add_env(&env, ft_strdup(tmp[0]), ft_strdup(tmp[1]));
		else
			ft_add_env(&env, ft_strdup(tmp[0]), ft_strdup(""));
		ft_afree((void **) tmp);
	}
	return (env);
}
