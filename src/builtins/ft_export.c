/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:10:14 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 23:53:03 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putenv(t_env **env, char **keys)
{
	char	*value;
	int		i;

	i = -1;
	while (keys[++i])
	{
		value = ft_get_env(*env, keys[i]);
		printf("declare -x %s=%s\n", keys[i], value);
		free(value);
	}
	ft_afree((void **) keys);
}

static void	ft_export_print(t_env **env)
{
	char	**keys;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	keys = ft_env_to_key_array(env);
	len = 0;
	while (keys[len])
		len++;
	i = -1;
	while (++i < len - 1)
	{
		j = -1;
		while (++j + i < len - 1)
		{
			if (ft_strncmp(keys[i], keys[i + j], -1) > 0)
			{
				tmp = keys[i];
				keys[i] = keys[i + j];
				keys[i + j] = tmp;
			}
		}
	}
	ft_putenv(env, keys);
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
