/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 00:20:34 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 01:45:38 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return ;
	while (str[i])
		free(str[i++]);
}

void	free_exec(t_cmd *cmd)
{
	t_exec	*ecmd;

	ecmd = (t_exec *)cmd;
	if (!ecmd)
		return ;
	free_args(ecmd->args);
	free_cmd(ecmd->cmd);
	free(ecmd);
	return ;
}

void	free_cmd2(t_cmd *cmd)
{
	t_redir		*rcmd;
	t_heredoc	*hcmd;

	if (cmd->type == REDIR)
	{
		rcmd = (t_redir *)cmd;
		free(rcmd->file);
		free_cmd(rcmd->cmd);
		free(rcmd);
	}
	else if (cmd->type == HEREDOC)
	{
		hcmd = (t_heredoc *)cmd;
		free(hcmd->file);
		free(hcmd->delim);
		free_cmd(hcmd->cmd);
		close(hcmd->open_file);
		free(hcmd);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_pipe		*pcmd;

	if (!cmd)
		return ;
	if (cmd->type == EXEC)
		free_exec(cmd);
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipe *)cmd;
		free_cmd(pcmd->left);
		free_cmd(pcmd->right);
		free(pcmd);
	}
	else if (cmd->type == REDIR || cmd->type == HEREDOC)
		free_cmd2(cmd);
}	
