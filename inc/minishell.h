/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:30 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/09 19:14:07 by pdeshaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{		
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell {
	int		stdin;
	int		stdout;
	int		stderr;
	int		status;

	int		pid_count;
	int		*pids;
	t_env	*env;
}	t_shell;

typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

t_shell *g_shell;

// Checks

void	ft_check(char *line, char **env);

void	ft_check_quotes(char *line, char **env);
void	ft_check_redir(char *line, char **env);
void	ft_check_pipe(char *line, char **env);

// Parsing

t_cmd	*parsing(char *line);

int		for_re(char *cmd, t_cmd *stru);
int		for_rre(char *cmd, t_cmd *stru);
void	throw_cases(char *cmd_b, t_cmd *cmd);
char	*conv_redir(char *cmd);
char	**conv_args(char *b_cmd);
char 	*get_first(char *cmd_b);
char	*skipSpasce(char *cmd_b);
int 	in_singlequote(char * cmd, int index);

// Execution

void	ft_exec(t_cmd *cmd, char **env);

pid_t	ft_exec_single(t_cmd *cmd, char **env);
pid_t	ft_exec_pipe(t_cmd *cmd, char **env);
pid_t	ft_exec_heredoc(t_cmd *cmd);
void	ft_exec_dup(t_cmd *cmd);

// Cmd struct utils

size_t	ft_cmdsize(t_cmd *cmd);
void	ft_default_cmd(t_cmd *cmd);

// Memory utils

void	*ft_memset(void *ptr, int value, size_t n);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memmove( void *destination, void *source, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_afree(void **arr);

// IO utils

void	ft_putstr_fd(char *s, int fd);

// Str utils

int		ft_chrcnt(char *str, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlen(char *str);
size_t	ft_strichr(char *s, int c);
size_t	ft_strlcpy(char *dst, char *src, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);

// Path utils

char	*ft_pathfind(char *cmd, char **env);
char	*ft_pathjoin(char *path, char *bin);



//debug 

void debug(t_cmd *cmd);


#endif
