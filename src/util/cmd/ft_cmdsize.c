/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:41:13 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/01 12:42:56 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_cmdsize(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (cmd && cmd->argv)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}
