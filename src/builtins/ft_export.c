/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:10:14 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/25 00:15:45 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_putenv(t_env **env, char **keys)
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
	return (0);
}

static int	ft_export_print(t_env **env)
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
	return (ft_putenv(env, keys));
}

int	ft_export(char **argv, t_env **env)
{
	char	*key;
	char	*val;
	int		i;

	if (!argv[1])
		return (ft_export_print(env));
	key = &argv[1][0];
	i = 0;
	while (argv[1][i] && argv[1][i] != '=')
		i++;
	if (!argv[1][i])
		return (0);
	argv[1][i] = '\0';
	val = &argv[1][i + 1];
	if (ft_is_valid_key(key))
		ft_set_env(env, ft_strdup(key), ft_strdup(val));
	else
	{
		ft_putstr_fd("Invalid key name.\n", 1);
		argv[1][i] = '=';
		return (1);
	}
	argv[1][i] = '=';
	return (0);
}
