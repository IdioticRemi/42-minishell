/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:19 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 14:17:36 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **argv, t_env **env)
{
	char	*key;

	if (!argv || !argv[1])
		return ;
	key = argv[1];
	if (!ft_is_valid_key(key))
		ft_putstr_fd("Invalid key name.\n", 1);
	else
		ft_del_env(env, key);
}
