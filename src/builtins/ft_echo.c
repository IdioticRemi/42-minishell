/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 14:05:37 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int fullN;
	int	newline;

	newline = 1;
	i = 1;
	fullN = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		newline = 0;
		while (argv[i][fullN])
		{
			if (argv[i][fullN] != 'n')
				newline = 1;
			fullN++;
		}
		if (newline == 1)
			break;
		fullN = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		write(1, " ", (argv[i] != NULL));
	}
	write(1, "\n", newline);
}
