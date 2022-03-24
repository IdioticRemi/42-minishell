/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:10:14 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 16:11:51 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	ft_putenv(char *key, char *value)
//{
//	printf("declare -x %s=%s\n", key, value);
//}

static void	ft_export_print(t_env **env)
{
	t_env	*start;
	t_env	*tmp;

	start = *env;
	tmp = *env;
	(void) start;
	(void) tmp;
}

void	ft_export(char **argv, t_env **env)
{
	char	*key;
	char	*val;
	int		i;

	if (!argv)
		return ;
	if (!argv[1])
	{
		ft_export_print(env);
		return ;
	}
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
