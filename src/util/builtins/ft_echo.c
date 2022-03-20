/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:09:42 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 19:14:19 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_echo(char **argv)
{
    int i;
    int temp;

    temp = 1;
    i = 1;
    while (ft_strncmp(argv[i], "-n", ft_strlen(argv[i])) == 0)
        i++;
    if (i == 1)
        temp = 0;
    while (argv[i])
    {
        write(1, argv[i], ft_strlen(argv[i]));
        i++;
    }
	if (temp)
        write(1, "\n", 1);
}