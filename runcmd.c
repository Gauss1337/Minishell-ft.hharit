/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 04:15:01 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 05:53:20 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

void	ft_wait(int	*p, pid_t id)
{
	int		exits;
	int		exit_status;

	close(p[0]);
	close(p[1]);
	waitpid(id, &exits, 0);
	wait(NULL);
	exit_status = WEXITSTATUS(exits);
	exit(exit_status);
}

void	ft_pipe(t_cmd *cmd, char **env, int built, t_list **env_l)
{
	t_pipe	*pcmd;
	t_par	icmd;

	pcmd = (t_pipe *)cmd;
	if (pipe(icmd.p) == -1)
		fail("pipe");
	icmd.id = fork();
	if (icmd.id == -1)
		fail("fork");
	if (icmd.id == 0)
	{
		close(icmd.p[0]);
		dup2(icmd.p[1], 1);
		close(icmd.p[1]);
		runcmd(pcmd->right, env, built, env_l);
	}
	icmd.id = fork();
	if (icmd.id == 0)
	{
		close(icmd.p[1]);
		dup2(icmd.p[0], 0);
		close(icmd.p[0]);
		runcmd(pcmd->left, env, built, env_l);
	}
	ft_wait(icmd.p, icmd.id);
}

void	ft_run_here(t_cmd *cmd, char **env, int built, t_list **env_l)
{
	t_heredoc	*hd;

	hd = (t_heredoc *)cmd;
	hd->open_file = open (hd->file, O_RDONLY, 0644);
	dup2(hd->open_file, 0);
	close(hd->open_file);
	unlink(hd->file);
	free(hd->file);
	runcmd(hd->cmd, env, built, env_l);
}

void	runcmd(t_cmd *cmd, char **env, int built, t_list **env_l)
{
	t_exec		*ecmd;
	t_redir		*rcmd;

	if (!cmd || g_glob.errors == 258)
		return ;
	if (cmd->type == PIPE)
		ft_pipe(cmd, env, built, env_l);
	else if (cmd->type == EXEC)
	{
		ecmd = (t_exec *)cmd;
		runcmd(ecmd->cmd, env, built, env_l);
		exec(ecmd, env, env_l, built);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redir *)cmd;
		check_file(rcmd);
		dup2(rcmd->open_file, rcmd->fd);
		runcmd(rcmd->cmd, env, built, env_l);
	}
	else if (cmd->type == HEREDOC)
		ft_run_here(cmd, env, built, env_l);
}
