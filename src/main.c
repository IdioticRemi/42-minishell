/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:15:26 by tjolivea          #+#    #+#             */
/*   Updated: 2022/02/03 15:02:56 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	t_shell	shell;
	char	*line;

	shell.stdin = dup(STDIN_FILENO);
	shell.stdout = dup(STDOUT_FILENO);
	shell.stderr = dup(STDERR_FILENO);

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("exit\n");
			exit(0);
		}
		dprintf(1, "(%s)\n", line);
		free(line);
	}
	return 0;
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_shell	shell;
// 	t_cmd	cmd;

// 	shell.stdin = dup(STDIN_FILENO);
// 	shell.stdout = dup(STDOUT_FILENO);
// 	shell.stderr = dup(STDERR_FILENO);

// 	cmd.in = ft_strdup("damn!\n");
// 	cmd.out = NULL;
// 	cmd.append = 0;
// 	cmd.heredoc = 1;

// 	cmd.argv = malloc(sizeof(char *) * 3);
// 	cmd.argv[0] = ft_strdup("cat");
// 	cmd.argv[1] = ft_strdup("-e");
// 	cmd.argv[2] = NULL;

// 	// cmd.next = NULL;
// 	cmd.next = malloc(sizeof(t_cmd));

// 	cmd.next->in = NULL;
// 	cmd.next->out = ft_strdup("output.txt");
// 	cmd.next->append = 0;
// 	cmd.next->heredoc = 0;
	
// 	cmd.next->argv = malloc(sizeof(char *) * 3);
// 	cmd.next->argv[0] = ft_strdup("cat");
// 	cmd.next->argv[1] = ft_strdup("-e");
// 	cmd.next->argv[2] = NULL;

// 	cmd.next->next = NULL;

// 	dprintf(1, "-----------------\n");
// 	for (t_cmd *t = &cmd; t; t = t->next)
// 	{
// 		if (t->heredoc)
// 			dprintf(1, "<< EOF ");
// 		else if (t->in)
// 			dprintf(1, "< %s ", t->in);
// 		for (int i = 0; t->argv[i]; i++)
// 			dprintf(1, "%s ", t->argv[i]);
// 		if (t->out)
// 			dprintf(1, "> %s", t->out);
// 		if (t->next)
// 			dprintf(1, "| ");
// 	}
// 	dprintf(1, "\n-----------------\n");
// 	dprintf(1, "\n-----------------\nExit code: %d\n-----------------\n",
// 		ft_exec(&shell, &cmd, env)
// 	);

// 	ft_afree((void **) cmd.argv);
// 	free(cmd.in);
// 	free(cmd.out);
// 	ft_afree((void **) cmd.next->argv);
// 	free(cmd.next->in);
// 	free(cmd.next->out);
// 	free(cmd.next);
// 	(void) argc;
// 	(void) argv;
// 	return (0);
// }
