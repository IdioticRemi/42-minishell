/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:10:14 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/23 20:21:50 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **argv, t_env **env)
{
	char	*key;
	char	*val;
	int		i;

	if (!argv || !argv[1])
		return ;
	key = &argv[1][0];
	i = 0;
	while (argv[1][i] && argv[1][i] != '=')
		i++;
	if (!argv[1][i])
		return ;
	argv[1][i] = '\0';
	val = &argv[1][i + 1];
	if (!ft_is_valid_key(key))
		ft_putstr_fd("Invalid key name.\n", 1);
	else
		ft_set_env(env, ft_strdup(key), ft_strdup(val));
	argv[1][i] = '=';
}

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
