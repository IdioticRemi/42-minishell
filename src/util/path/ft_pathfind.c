/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:47:04 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/01 12:22:05 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pathfind(char *cmd, char **env)
{
	char	*path_str;
	char	**path;
	char	*loc;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path_str = env[i] + 5;
	path = ft_split(path_str, ':');
	i = 0;
	while (path && path[i])
	{
		loc = ft_pathjoin(path[i], cmd);
		if (!access(loc, F_OK))
		{
			ft_afree((void **)path);
			return (loc);
		}
		free(loc + (0 * i++));
	}
	ft_afree((void **)path);
	return (cmd);
}
