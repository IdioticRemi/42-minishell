# include "../../include/header.h"

char *conv_redir(char *cmd)
{
    int i;
    char *new;
    char *start;
    char *end;
    char *temp;

    i = 0;
    new = ft_strdup(cmd);
    free(cmd);
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
            while (new[i] == '>' || new[i] == '<' || new[i] == ' ')
                i++;
            while (new[i] != ' ')
                i++;
            while (new[i] == ' ')
                i++;
            end = ft_substr(new, i, ft_strlen(new + i));
            free(new);
            new = ft_strjoin(start, end);
            free(start);
            start = NULL;
            free(end);
            end = NULL;
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
    mode = -1;
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

    path = NULL;
    mode = -1;
    is_open = -1;
    i = 0;
    while (cmd[i])
    {
        if (is_open > 0)
            close(is_open);
        if (cmd[i] == '<')
        {
            free(path);
            path = NULL;
            if (cmd[i + 1] && cmd[i + 1] == '<')
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
            is_open = open(path, O_RDONLY | O_CREAT, 0777);;
        }
        i++;
    }
    stru->append = mode;
    stru->in = path;
    return (mode);
}
