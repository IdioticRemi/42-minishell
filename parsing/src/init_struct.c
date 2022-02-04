#include "../include/header.h"

void default_cmd(t_cmd *cmd)
{
	cmd->append = -1;
	cmd->args = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->next = NULL;
}