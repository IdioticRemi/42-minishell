/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:30 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/03 14:48:27 by tjolivea         ###   ########.fr       */
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

typedef struct s_shell {
	int	stdin;
	int	stdout;
	int	stderr;
}	t_shell;

typedef struct s_cmd {
	char			*in;
	char			*out;
	int				heredoc;
	int				append;
	char			**argv;
	struct s_cmd	*next;
}	t_cmd;

// Execution

int		ft_exec(t_shell *shell, t_cmd *cmd, char **env);

pid_t	ft_exec_single(t_shell *shell, t_cmd *cmd, char **env);
pid_t	ft_exec_pipe(t_shell *shell, t_cmd *cmd, char **env);
pid_t	ft_exec_heredoc(t_cmd *cmd);
void	ft_exec_dup(t_cmd *cmd);

// Cmd struct utils

size_t	ft_cmdsize(t_cmd *cmd);

// Memory utils

void	*ft_memset(void *ptr, int value, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_afree(void **arr);

// IO utils

void	ft_putstr_fd(char *s, int fd);

// Str utils

size_t	ft_strlen(char *str);
size_t	ft_strichr(char *s, int c);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *src);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlcpy(char *dst, char *src, size_t n);
char	**ft_split(char *s, char c);

// Path utils

char	*ft_pathfind(char *cmd, char **env);
char	*ft_pathjoin(char *path, char *bin);

#endif
