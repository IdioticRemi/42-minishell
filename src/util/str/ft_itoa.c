/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcnt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:09:43 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 15:42:06 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long	ft_abs(long x)
{
	return ((x < 0) * -x + (x >= 0) * x);
}

static size_t	ft_nbrlen(int n)
{
	size_t	len;

	len = 1 + (n < 0);
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	n_len;
	long	x;
	char	*str;

	x = n;
	n_len = ft_nbrlen(n);
	str = malloc(n_len + 1);
	if (!str)
		return (0);
	str[n_len] = '\0';
	if (x < 0)
		str[0] = '-';
	while (n_len > (n < 0))
	{
		str[--n_len] = ft_abs(x % 10) + '0';
		x /= 10;
	}
	return (str);
}
