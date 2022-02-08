# include <stdlib.h>
# include <stdio.h>
 #include <fcntl.h>
#include <unistd.h>

typedef struct s_cmd {
  char		*in;
  char		*out;
  int		append; // (0 = non symbole: ">" ou rien, 1 = oui symbole: ">>")
  char		**args;
  struct s_cmd		*next;
}  t_cmd;

typedef struct s_env {
  char		*key;
  char		*value;
  struct s_env		*next;
}  t_env;

//debug
void debug(t_cmd *cmd);

//utils
void corr_free(char *str);
void	*ft_memcpy( void *destination, const void *source, size_t size );
int ft_strchr(const char *string, int searchedChar);
char	*ft_strdup(char *src);
char	**ft_split(char *str, char *charset);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_stict_split(char *str, char *charset);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	*ft_memmove( void *destination, const void *source, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

//parsing
void	default_cmd(t_cmd *cmd);
void throw_cases(char *cmd_b, t_cmd *cmd);
char **conv_args(char *b_cmd);
int free_all(char **str);

//redirections
int for_re(char *cmd, t_cmd *stru);
int for_rre(char *cmd, t_cmd *stru);
char *conv_redir(char *cmd);

//env
int add_env(t_env *env, char *key, char *value);
t_env *delone_env(t_env *env, char *key);