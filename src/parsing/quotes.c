/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:58 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 15:18:29 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int in_singlequote(char * cmd, int index)
{
	int i;
	int bool_quote;

	i = index;
	bool_quote = 0;
	while(i >= 0)
	{
		if ((cmd[i] == '\'') && bool_quote == 0)
			bool_quote = 1;
		else if ((cmd[i] == '\'') && bool_quote == 1)
			bool_quote = 0;
		i--;
	}
	return bool_quote;
}

int in_doublequote(char * cmd, int index)
{
	int i;
	int bool_quote;

	i = index;
	bool_quote = 0;
	while(i >= 0)
	{
		if ((cmd[i] == '"') && bool_quote == 0)
			bool_quote = 1;
		else if ((cmd[i] == '"') && bool_quote == 1)
			bool_quote = 0;
		i--;
	}
	return bool_quote;
}

int in_quote(char * cmd, int index)
{
	if (in_singlequote(cmd, index) == 1)
		return (1);
	else if (in_doublequote(cmd, index) == 1)
	{
		if (cmd[index] == '$')
			return (0);
		return (1);
	}
	return (0);
}

void reset_temp(char * start, char * end)
{
	if (start)
		free(start);
	if (end)
		free(end);
	end = NULL;
	start = NULL;
}

int get_next_space(char * cmd, int index)
{
	int i;

	i = index;
	while (cmd[i] != '\0' && cmd[i] != ' ')
		i++;
	return (i);
}


char	*ft_own_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;

	if (!s1)
		return (s2);
	else if (!s2)
		return (s1);
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	ft_memcpy(result, s1, ft_strlen((char *)s1));
	ft_memcpy(result + ft_strlen((char *)s1), s2, ft_strlen((char *)s2));
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
	return (result);
}

char * with_var(char *brut, t_env *env)
{
	(void)env;
	char * result;
	char * tempResult;
	int i;
	char * tempStart;
	char * tempEnd;

	tempStart = NULL;
	tempEnd = NULL;
	i = 0;
	result = ft_strdup(brut);
	while(result[i])
	{
		if (result[i] == '$' && in_quote(result, i) == 0 && result[i + 1] && result[i + 1] != ' ')
		{
			if (i > 0)
				tempStart = ft_substr(result, 0, i - 1);
			tempEnd = ft_substr(result, get_next_space(result, i), ft_strlen(result) -  get_next_space(result, i));
			if (tempStart)
				tempStart = ft_own_strjoin(tempStart, ft_strdup(" "));
			tempResult = ft_own_strjoin(tempStart, ft_strdup("pr$t")); //get_env_var(brut , i)
			free(result);
			i = ft_strlen(tempResult);
			result = ft_own_strjoin(tempResult, tempEnd);
		}
		else
			i++;
	}
	return result;
}