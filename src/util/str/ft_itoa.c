/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:09:43 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/07 16:10:12 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	int_count(int nb)
{
	int	count;

	count = 0;
	if (nb < 0 )
		count++;
	while (nb / 10)
	{
		count++;
		nb /= 10;
	}
	return (count + 1);
}

char	*ft_itoa(int nb)
{
	char			*result;
	int				index;

	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	index = int_count(nb);
	result = malloc(sizeof(char) * int_count(nb) + 1);
	if (result == NULL)
		return (NULL);
	result[index] = '\0';
	if (nb < 0)
		result[0] = '-';
	while (nb / 10)
	{
		result[index - 1] = ((nb % 10) >= 0) * (nb % 10)
			+ ((nb % 10) < 0) * -(nb % 10) + '0';
		index--;
		nb /= 10;
	}
	result[index - 1] = ((nb % 10) >= 0) * (nb % 10)
		+ ((nb % 10) < 0) * -(nb % 10) + '0';
	return (result);
}