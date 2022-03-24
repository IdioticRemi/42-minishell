/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:33:10 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 23:38:00 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_key_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = ft_env_size(env);
	arr = malloc(sizeof(char *) * (env_size + 1));
	arr[env_size] = NULL;
	if (!env_size)
		return (arr);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		arr[i++] = ft_strdup(tmp->key);
		tmp = tmp->next;
	}
	return (arr);
}

char	**ft_env_to_array(t_env **env)
{
	char	**arr;
	t_env	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = ft_env_size(env);
	arr = malloc(sizeof(char *) * (env_size + 1));
	arr[env_size] = NULL;
	if (!env_size)
		return (arr);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		arr[i++] = ft_env_join(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (arr);
}
