# include "include/header.h"

void debug(t_cmd *cmd)
{
	int i; 
	int y;

	y = 0;
	while (cmd != NULL)
	{

		i = -1;
		printf("========= %d ==========\n", y);
		printf("in : %s\n", cmd->in);
		printf("out : %s\n", cmd->out);
		if (cmd->args && cmd->args[0])
			while (cmd->args[++i])
				printf("args : %s\n", cmd->args[i]);
		else
			printf("args : %s\n", NULL);
		printf(">> : %d\n", cmd->append);
		cmd = cmd->next;
		y++;
	}
}