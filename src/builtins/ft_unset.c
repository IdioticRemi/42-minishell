/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:17:19 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/28 13:32:13 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_unset_err(char *err)
{
	ft_putstr_fd("Invalid key name: '", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("'.\n", STDERR_FILENO);
	return (1);
}

int	ft_unset(char **argv, t_env **env)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (argv[++i])
	{
		if (!ft_is_valid_key(argv[i]))
			status += ft_unset_err(argv[i]);
		ft_del_env(env, argv[i]);
	}
	return (status != 0);
}
