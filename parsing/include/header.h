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

void debug(t_cmd *cmd);

void throw_cases(char *cmd_b, t_cmd *cmd);
void part1_cases(char *cmd_b, t_cmd *cmd);
int ft_strchr(const char *string, int searchedChar);
char	*ft_strdup(char *src);
void	default_cmd(t_cmd *cmd);
char	**ft_split(char *str, char *charset);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_stict_split(char *str, char *charset);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
void	*ft_memcpy( void *destination, const void *source, size_t size );
int free_all(char **str);
char *cancel_bonus(char *str);
void	*ft_memmove( void *destination, const void *source, size_t size);
char **conv_args(char *b_cmd);

int for_re(char *cmd, t_cmd *stru);
int for_rre(char *cmd, t_cmd *stru);