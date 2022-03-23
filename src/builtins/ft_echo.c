/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/22 18:03:00 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argv)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (argv[i] && ft_strequ(argv[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], 1);
		write(1, " ", (argv[i] != NULL));
	}
	write(1, "\n", newline);
}
