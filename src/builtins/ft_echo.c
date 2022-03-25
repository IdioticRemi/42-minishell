/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/25 13:15:10 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_echo_bis(char **argv, int newline, int i)
{
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		write(1, " ", (argv[i] != NULL));
	}
	write(1, "\n", newline);
	return (0);
}

int	ft_echo(char **argv)
{
	int	i;
	int	full_n;
	int	newline;

	newline = 1;
	i = 1;
	full_n = 1;
	while (argv[i] && ft_strncmp(argv[i], "-n", 2) == 0)
	{
		newline = 0;
		while (argv[i][full_n])
		{
			if (argv[i][full_n] != 'n')
				newline = 1;
			full_n++;
		}
		if (newline == 1)
			break ;
		full_n = 1;
		i++;
	}
	return (ft_echo_bis(argv, newline, i));
}
