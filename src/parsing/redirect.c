/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:14:21 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/22 17:37:55 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char **ft_realloc(char **str, char *value)
{
    char **final;
    int i;

    i = -1;
    if (str == NULL)
    {
        final = (char **)malloc(sizeof(char *) * 2);
        i++;
    }
    else
    {
        while (str[++i]);
        final = (char **)malloc(sizeof(char *) * (i + 2));
        i = -1;
        while (str[++i])
            final[i] = ft_strdup(str[i]);
    }
    final[i] = value;
    final[i + 1] = NULL;
    if (str)
        ft_afree((void **)str);
    return (final);
}

size_t ft_max(size_t a, size_t b)
{
    if (a < b)
        return (b);
    return (a);
}

char * set_s(char *line, char *cmd_final, int isInquote)
{
    char *temp;
    char *final;
    char *temp2;

    temp2 = NULL;
    if (isInquote == 0)
    {
        temp2 = with_var(line, NULL, NULL, 0); //env
        temp = ft_strjoin(temp2, "\n");
    }
    else
        temp = ft_strjoin(line, "\n");
    if (cmd_final)
    	final = ft_strjoin(cmd_final, temp);
    else
		final = ft_strdup(temp);
    free(temp);
    if (temp2)
        free(temp2);
    if (cmd_final)
		free(cmd_final);
    return final;
}

int checkHereDocQuote(char * end)
{
    int i;

    i = 0;

        while(end[i])
        {
            if (end[i] == '\'' || end[i] == '"')
                return (1); 
            i++;
        }

    return (0);
}

char * heredoc_c(char **end, t_cmd *stru)
{
    int i;
    int bool_quote;
    char	*line;
    char *final_line;
	char *temp;

    final_line = NULL;
    i = 0;
    while (end[i])
    {
        line = readline("\033[31mHEREDOC\033[0m> ");
        if (!line)
            break;
		temp = without_quote(end[i]);
        if (ft_strncmp(line, temp, ft_max(ft_strlen(line), ft_strlen(end[i]))) == 0)
            i++;
        if (end[i])
            bool_quote = checkHereDocQuote(end[i]);
        else
            bool_quote = 0;
        if (end[i])
            final_line = set_s(line, final_line, bool_quote);
        free(line);
		free(temp);
    }
    stru->heredoc = 1;
    ft_afree((void **)end);
    if (!final_line)
        return(ft_strdup(""));
    return (final_line);
}


char *conv_redir(char *cmd)
{
    int i;
    char *new;
    char *start;
    char *end;
    char *temp;

    i = 0;
    new = ft_strdup(cmd);
    while (new[i])
    {
        if ((new[i] == '>' || new[i] == '<') && in_quote(cmd, i, 0) == 0)
        {
            
            start = ft_substr(new, 0, i);
            if (new[i + 1] && (new[i + 1] == '>' || new[i + 1] == '<'))
                i++;
            if (new[i + 1] && new[i + 1] != ' ')
            {
                temp = ft_strjoin(start, " ");
                free(start);
                start = temp;
            }
            while (new[i] && (new[i] == '>' || new[i] == '<' || new[i] == ' '))
                i++;
            while (new[i] && (new[i] != ' ' || in_quote(new, i, 0) == 1))
                i++;
            while (new[i] && new[i] == ' ')
                i++;
            end = ft_substr(new, i, ft_strlen(new + i));
            free(new);
            new = ft_strjoin(start, end);
            free(start);
            free(end);
            i = 0;
        }
        i++;
    }
    
    return (new);
}

char *get_next(char *cmd, int index)
{
    int i;
    int start;

    start = index + 1;
    if (!cmd[start])
        return (NULL);
    while (cmd[start] == ' ')
        start++;
    i = start;
    while ((cmd[i] != ' ' || in_quote(cmd, i, 0) == 1) && cmd[i] != '\0')
        i++;
    return(ft_substr(cmd, start, i - start));
}


int for_re(char *cmd, t_cmd *stru)
{
    int i;
    char *path;
    int mode;
    int is_open;

    path = NULL;
    mode = 0;
    is_open = -1;
    i = 0;
    while (cmd[i])
    {
        if (is_open > 0)
            close(is_open);
        if (cmd[i] == '>' && in_quote(cmd, i, 0) == 0)
        {
            free(path);
            path = NULL;
            if (cmd[i + 1] && cmd[i + 1] == '>')
            {
                mode = 2;
                path = get_next(cmd, i + 1);
                i++;
            }    
            else
            {
                mode = 1;
                path = get_next(cmd, i);
            }
            is_open = open(path, O_WRONLY | O_CREAT, 0777);
            if (is_open < 0)
            {
				ft_putstr_fd(path, 2);
                ft_putstr_fd(" : Cannot access file or directory\n", 2);
                return (-1);
            }
        }
        i++;
    }
    stru->append = mode;
    stru->out = path;
    return (mode);
}

int for_rre(char *cmd, t_cmd *stru)
{
    int i;
    char *path;
    int mode;
    int is_open;
    char **heredoc;
    int j;
    char *temp;
    
    j = 0;
    heredoc = NULL;
    path = NULL;
    mode = 0;
    temp = NULL;
    is_open = -1;
    i = 0;
    while (cmd[i])
    {
        if (is_open > 0)
            close(is_open);
        if (cmd[i] == '<' && in_quote(cmd, i, 0) == 0)
        {
			if (path)
            	free(path);
            if (cmd[i + 1] && cmd[i + 1] == '<')
            {
                heredoc = ft_realloc(heredoc, get_next(cmd, i + 1));
                j++;
                i += 2;
                continue;
            }
            else
            {
                mode = 1;
				temp = get_next(cmd, i);
                path = without_quote(temp); //dangereux leaks =============================================================
            }
            is_open = open(path, O_RDONLY);
            if (is_open < 0)
            {
				ft_putstr_fd(path, 2);
                ft_putstr_fd(" : Cannot access file or directory\n", 2);
                return (-1);
            }
			if (temp)
				free(temp);
			temp = NULL;
        }
        i++;
    }
    if (heredoc)
        temp = heredoc_c(heredoc, stru);
    if (temp != NULL)
        stru->in = temp;
    else
        stru->in = path;
    
    stru->append = mode;
    return (mode);
}
