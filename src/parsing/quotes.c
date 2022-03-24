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
		if (cmd[i] == '\'' && bool_quote == 0 && in_doublequote(cmd,i) == 0)
			bool_quote = 1;
		else if ((cmd[i] == '\'') && bool_quote == 1 && in_doublequote(cmd,i) == 0)
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
		if ((cmd[i] == '"') && bool_quote == 0 && in_singlequote(cmd,i) == 0)
			bool_quote = 1;
		else if ((cmd[i] == '"') && bool_quote == 1 &&  in_singlequote(cmd,i) == 0)
			bool_quote = 0;
		i--;
	}
	return bool_quote;
}

int in_quote(char * cmd, int index, int dollars)
{
	if (in_singlequote(cmd, index) == 1)
		return (1);
	else if (in_doublequote(cmd, index) == 1)
	{
		if (dollars && cmd[index] == '$')
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
	while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '?'  && cmd[i] != '$' && cmd[i] != '"' && cmd[i] != '\'')
		i++;
	return (i);
}


char	*ft_own_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
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

char *get_first_quotes(char *cmd_b)
{
	int i;
	
	i = 0;
	while (cmd_b[i] && cmd_b[i] != ' ' && cmd_b[i] != '\n' && in_quote(cmd_b, i, 1) == 0)
		i++;
	return (ft_substr(cmd_b, 0, i));
}

char * with_var(char *brut)
{
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
		if (result[i] == '$' && in_quote(result, i, 1) == 0 && result[i + 1] && result[i + 1] != ' ')
		{
			if (i > 0)
				tempStart = ft_substr(result, 0, i);
			if (result[i + 1] == '?')
			{
				tempResult = ft_own_strjoin(tempStart, ft_itoa(g_shell->status));
				tempEnd = ft_substr(result, get_next_space(result, i + 1) + 1, ft_strlen(result) -  (get_next_space(result, i + 1) + 1));
			}
			else
			{
				tempEnd = ft_substr(result, get_next_space(result, i + 1), ft_strlen(result) -  get_next_space(result, i));
				free(result);
				result = get_first_quotes(brut + i + 1);
				tempResult = ft_own_strjoin(tempStart, ft_get_env(g_shell->env  , result));
			}
			free(result);
			i = ft_strlen(tempResult);
			result = ft_own_strjoin(tempResult, tempEnd);
		}
		else
			i++;
	}
	return result;
}

char * without_quote(char * cmd)
{
	int i;
	char *result;
	char *start;
	char *end;

	result = ft_strdup(cmd);
	i = 0;
	start = NULL;
	end = NULL;

	while (result[i])
	{
		if (((result[i] == '\'' && in_doublequote(cmd, i) == 0)
			|| (result[i] == '"' && in_singlequote(cmd, i) == 0)))
		{
			start = ft_substr(result, 0, i);
			end = ft_substr(result, i + 1, ft_strlen(result) - i);
			free(result);
			result = ft_own_strjoin(start, end);
			i = 0;
		}
		else
			i++;
	}
	return result;
}


void without_quote_thing(char ** thing)
{
	char *temp;

	temp = ft_strdup(*thing);
	free(*thing);
	*thing = without_quote(temp);
	free(temp);
}

void without_quote_args(t_cmd *env)
{
	int i;
	char *temp;

	temp = NULL;
	i = 0;
	while (env->argv[i])
	{
		without_quote_thing(&env->argv[i]);
		i++;
	}
	if (env->out)
		without_quote_thing(&env->out);
	if (env->in)
		without_quote_thing(&env->in);
}
