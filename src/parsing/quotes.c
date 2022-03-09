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

char * with_var(char *brut)
{
	int i;

	i = 0;
	while(brut[i])
	{
		i++;
	}
	return NULL;
}