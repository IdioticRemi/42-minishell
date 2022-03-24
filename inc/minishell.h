/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeshaye <pdeshaye@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:30 by tjolivea          #+#    #+#             */
/*   Updated: 2022/03/24 16:32:28 by tjolivea         ###   ########lyon.fr   */
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
# include <termios.h>

typedef struct s_env
{		
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell {
	int			stdin;
	int			stdout;
	int			stderr;
	int			status;

	tcflag_t	c_lflag;
	int			pid_count;
	int			*pids;
	t_env		*env;
}	t_shell;

typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

t_shell	*g_shell;

// Main

void	ft_clean_exit(void);

// Checks

void	ft_check(char *line);

void	ft_check_quotes(char *line);
void	ft_check_redir(char *line);
void	ft_check_pipe(char *line);

// Parsing

t_cmd	*parsing(char *line);

int		for_re(char *cmd, t_cmd *stru);
int		for_rre(char *cmd, t_cmd *stru);
void	throw_cases(char *cmd_b, t_cmd *cmd);
char	*conv_redir(char *cmd);
char	**conv_args(char *b_cmd);
char	*get_first(char *cmd_b);
char	*skipSpasce(char *cmd_b);
int		in_quote(char *cmd, int index, int dollars);
char	*with_var(char *brut, char *tempStart, char *tempEnd, int i);
size_t	ft_max(size_t a, size_t b);
char	*without_quote(char *cmd);
void	without_quote_args(t_cmd *env);
int		in_doublequote(char *cmd, int index);

// Execution

void	ft_exec(t_cmd *cmd);

//void	ft_exec_builtin(t_cmd *cmd, t_env **env);
pid_t	ft_exec_single(t_cmd *cmd, t_env **env);
pid_t	ft_exec_pipe(t_cmd *cmd, t_env **env);
pid_t	ft_exec_heredoc(t_cmd *cmd);
void	ft_exec_dup(t_cmd *cmd);

// Builtins

void	ft_exit(t_cmd *cmd);
void	ft_null(void);
void	ft_pwd(void);
void	ft_echo(char **argv);
void	ft_export(char **argv, t_env **env);
void	ft_unset(char **argv, t_env **env);
void	ft_env(t_env **env);

// Environement

t_env	*ft_parse_env(char **_env);
char	**ft_env_to_key_array(t_env **env);
char	**ft_env_to_array(t_env **env);

// Cmd struct utils

size_t	ft_cmdsize(t_cmd *cmd);
void	ft_default_cmd(t_cmd *cmd);
void	ft_free_cmd(t_cmd *cmd);

// Env struct utils

size_t	ft_env_size(t_env **env);
void	ft_set_env(t_env **env, char *key, char *value);
char	*ft_env_join(char *key, char *value);
void	ft_free_env(t_env *env);
void	ft_del_env(t_env **env, char *key);
char	*ft_get_env(t_env *env, char *key);

// Memory utils

void	*ft_memset(void *ptr, int value, size_t n);
void	*ft_memcpy(void *dst, void *src, size_t n);
void	*ft_memmove( void *destination, void *source, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_afree(void **arr);

// IO utils

void	ft_putstr_fd(char *s, int fd);
void	ft_termios_init(void);
void	ft_termios_revert(void);

// Char utils

int		ft_isalpha(char c);
int		ft_isdigit(char c);

// Str utils

int		ft_chrcnt(char *str, char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strequ(char *s1, char *s2);
size_t	ft_strlen(char *str);
size_t	ft_strichr(char *s, int c);
size_t	ft_strlcpy(char *dst, char *src, size_t n);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
int		ft_atoi(const char *nptr);
char	*ft_itoa(int nbr);
char	**ft_split_quote(char *s, char c);

// Path utils

char	*ft_pathfind(char *cmd, char **env);
char	*ft_pathjoin(char *path, char *bin);

// Builtin Utils

int		ft_is_builtin(t_cmd *cmd);
int		ft_is_valid_key(char *key);

//debug 

void	debug(t_cmd *cmd);

#endif