/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 01:17:19 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/28 14:37:38 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "minishell.h"

static int	ft_err(char *err_msg, char *str, int err)
{
	if (str)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
	}
	else
		ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (err);
}

static int	ft_chdir(char *path)
{
	struct stat	s;

	if (chdir(path) < 0)
	{
		if (stat(path, &s) == -1)
		{
			ft_err("no such file or directory.", path, 1);
			return (127);
		}
		else if (!(s.st_mode & S_IRUSR))
			ft_err("permission denied.", path, 126);
		else
			ft_err("not a directory.", path, 126);
		return (1);
	}
	return (0);
}

static int	ft_navto(t_env **env, char *path, int abs)
{
	char	*old;
	char	*new;

	if (!path)
		return (ft_err("cd: an env variable is missing.", NULL, 1));
	old = ft_get_env(*env, "PWD");
	if (!old)
		old = getcwd(NULL, 0);
	ft_set_env(env, ft_strdup("OLDPWD"), ft_strdup(old));
	new = path;
	if (!abs)
	{
		new = ft_pathjoin(old, path);
		free(path);
	}
	abs = ft_chdir(new);
	free(old);
	free(new);
	ft_set_env(env, ft_strdup("PWD"), getcwd(NULL, 0));
	return (abs);
}

static int	ft_bridge_nav(t_env **env, char *path)
{
	char	*tmp;
	char	*home;

	if (!ft_strncmp(path, "~/", 2))
	{
		home = ft_get_env(*env, "HOME");
		tmp = path;
		path = ft_pathjoin(home, tmp + 2);
		free(tmp);
		free(home);
		return (ft_navto(env, path, 1));
	}
	return (ft_navto(env, path, 0));
}

int	ft_cd(char **argv, t_env **env)
{
	if (!argv[1] || ft_strequ("~", argv[1]) || ft_strequ("--", argv[1]))
		return (ft_navto(env, ft_get_env(*env, "HOME"), 1));
	if (argv[1] && argv[2])
		return (ft_err("cd: too many arguments.", NULL, 1));
	if (ft_strequ("-", argv[1]))
		return (ft_navto(env, ft_get_env(*env, "OLDPWD"), 1));
	if (argv[1][0] == '/')
		return (ft_navto(env, ft_strdup(argv[1]), 1));
	return (ft_bridge_nav(env, ft_strdup(argv[1])));
}
