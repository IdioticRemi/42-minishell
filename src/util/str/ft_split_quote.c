/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:06:41 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/22 16:32:45 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_all(char **arr, int i)
{
	while (i > 0)
		free(arr[i--]);
	free(arr);
}

static int	ft_wordcount(char *s, char c)
{
	int		wc;
	int		i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (((s[i] != c && ((in_quote(s, i, 0) == 0 && (
								s[i] != '"' && s[i] != '\'')) || (in_quote(
								s, i, 0) == 1 && (
								s[i] == '"' || s[i] == '\''))))) && s[i])
			wc++;
		while ((s[i] != c || in_quote(s, i, 0) == 1) && s[i])
			i++;
	}
	return (wc);
}

static char	*ft_create_word(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && (s[i] != c || in_quote(s, i, 0) == 1))
		i++;
	str = ft_calloc(i + 1, 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s, i + 1);
	return (str);
}

char	**ft_split_quote(char *s, char c)
{
	int		i;
	int		wc;
	char	**arr;

	if (!s)
		return (0);
	wc = ft_wordcount(s, c);
	arr = ft_calloc(wc + 1, sizeof(char *));
	if (!arr)
		return (0);
	i = -1;
	while (++i < wc)
	{
		while (*s == c && in_quote(s, 0, 0) == 0)
			s++;
		arr[i] = ft_create_word(s, c);
		if (!arr[i])
		{
			ft_free_all(arr, i);
			return (0);
		}
		s = s + ft_strlen(arr[i]);
	}
	arr[i] = 0;
	return (arr);
}
