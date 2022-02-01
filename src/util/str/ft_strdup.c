/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:27:29 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/01 14:27:37 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	char	*dup;
	size_t	src_len;

	src_len = ft_strlen(src) + 1;
	dup = malloc((src_len) * sizeof(char));
	if (!dup)
		return (0);
	return (ft_memcpy(dup, src, src_len));
}
