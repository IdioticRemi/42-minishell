/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:14:21 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/10 14:43:31 by pdeshaye         ###   ########.fr       */
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

void set_s(char *line, t_cmd *stru, char *cmd)
{
    t_cmd *new;
    char *cmd_true;

    while (stru->next)
        stru = stru->next;
    new = malloc(sizeof(t_cmd));
    ft_default_cmd(new);
    cmd_true = conv_redir(cmd);
	new->argv = conv_args(cmd_true);
	new->argv[0] = get_first(cmd_true);
    new->argv = ft_realloc(new->argv, line);
    new->heredoc = 1;
    stru->next = new;
    free(cmd_true);
}

int heredoc_c(char **end, t_cmd *stru, char *cmd)
{
    int i;
    char	*line;
    
    i = 0;
    while (end[i])
    {
        line = readline("\033[31mHEREDOC\033[0m> ");
        if (!line)
            break;
        if (ft_strncmp(line, end[i], ft_max(ft_strlen(line), ft_strlen(end[i]))) == 0)
            i++;
        if (end[i])
            set_s(line, stru, cmd);
    }
    stru->heredoc = 1;
    ft_afree((void **)end);
    return (0);
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
        if (new[i] == '>' || new[i] == '<')
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
            while (new[i] && new[i] != ' ')
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
    while (cmd[i] != ' ' && cmd[i] != '\0')
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
        if (cmd[i] == '>')
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
            is_open = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
            if (is_open < 0)
            {
                write(2, path, ft_strlen(path));
                ft_putstr_fd(" : Permisson denied\n", 2);
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
    
    j = 0;
    heredoc = NULL;
    path = NULL;
    mode = 0;
    is_open = -1;
    i = 0;
    while (cmd[i])
    {
        if (is_open > 0)
            close(is_open);
        if (cmd[i] == '<')
        {
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
                path = get_next(cmd, i);
            }
            is_open = open(path, O_RDONLY | O_CREAT, 0777);
            if (is_open < 0)
            {
                write(2, path, ft_strlen(path));
                ft_putstr_fd(" : Permisson denied\n", 2);
                return (-1);
            }
        }
        i++;
    }
    if (heredoc)
        heredoc_c(heredoc, stru, cmd);
    stru->append = mode;
    stru->in = path;
    return (mode);
}
