# include "../include/header.h"

int white_spasce(char *str)
{
	int i;

	i = ft_strlen(str);
	if (i == 0)
		return (1);
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
		i--;
	}
	return (i);
}

char *get_first(char *cmd_b)
{
	int i;
	
	i = 0;
	while (cmd_b[i] && cmd_b[i] != ' ' && cmd_b[i] != '\n')
		i++;
	return (ft_substr(cmd_b, 0, i));
}

char *skipSpasce(char *cmd_b)
{
	int i;
	char *res;

	i = 0;
	if (white_spasce(cmd_b) == 0)
		return (cmd_b);
	while (cmd_b[i] && cmd_b[i] == ' ')
		i++;
	res = ft_substr(cmd_b, i, ft_strlen(cmd_b) - i);
	free(cmd_b);
	return (res);
}

void fill_cmd(char *cmd_b, t_cmd *cmd)
{
	t_cmd *next;
	char *cmd_true;

	next = malloc(sizeof(t_cmd));
	if (next == NULL)
		return;
	default_cmd(next);
	cmd_true = skipSpasce(ft_strdup(cmd_b));
	free(cmd_b);
	cmd->v_cmd = get_first(cmd_true);
	cmd->args = conv_args(cmd_true);
	free(cmd_true);
	cmd->next = next;
}

void throw_cases(char *cmd_b, t_cmd *cmd)
{
	char **b_sep;
	int i;

	b_sep = ft_stict_split(cmd_b, "|");
	i = 0;
	while (b_sep[i])
	{
		fill_cmd(b_sep[i], cmd);
		cmd = cmd->next;
		i++;
	}
}

void part1_cases(char *cmd_b, t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd_b[i])
	{
		if (cmd_b[i] == ';')
			NULL;
		i++;
	}
}
