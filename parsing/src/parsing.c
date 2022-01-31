# include "../include/header.h"

char *convert_brut(char **av)
{
	char *brut_cmd;
	int i;
	
	i = 1;
	brut_cmd = malloc(1);
	while (av[i])
	{
		brut_cmd = ft_strjoin(brut_cmd, av[i]);
		i++;
	}
	return (brut_cmd);
}

t_cmd parsing(int ac, char **av)
{
	t_cmd cmd;
	char *brut_cmd;

	default_cmd(&cmd);
	brut_cmd = cancel_bonus(convert_brut(av));
	throw_cases(brut_cmd, &cmd);
	return (cmd);
}

int main(int ac, char **av)
{

	t_cmd cmd = parsing(ac, av);

	debug(&cmd);

	return (0);
}