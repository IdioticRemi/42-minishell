/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:45:13 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/17 19:42:57 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int export_v(t_env *env, char *key, char *value)
{
    if (!env || !key || !value)
        return (1);
    ft_add_env(&env, key, value);
    return (0);
}