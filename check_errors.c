/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:06:53 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 04:26:22 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file2(t_redir *rcmd)
{
	DIR	*dir;

	rcmd->open_file = open(rcmd->file, rcmd->flags, 0644);
	if (rcmd->fd)
	{
		dir = opendir(rcmd->file);
		if (dir)
		{
			closedir(dir);
			return (0);
		}
	}
	if (!rcmd->fd && rcmd->open_file < 0)
		return (0);
	rcmd->open_file = open(rcmd->file, rcmd->flags | O_CREAT, 0644);
	return (1);
}

int	check_errors(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	while (cmd)
	{
		if (cmd->type == EXEC)
			cmd = ((t_exec *)cmd)->cmd;
		else if (cmd->type == REDIR)
		{
			if (!check_file2((t_redir *)cmd))
				return (0);
			cmd = ((t_redir *)cmd)->cmd;
		}
		else if (cmd->type == HEREDOC)
			cmd = ((t_heredoc *)cmd)->cmd;
	}
	return (1);
}

void	not_f_dir(char *str, int exit_value)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" : No such file or directory", 2);
	exit(exit_value);
}

void	is_dir(char *str, DIR *dir, int exit_value)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" : Is a directory", 2);
	closedir(dir);
	exit(exit_value);
}

void	perm_denied(char *str, int exit_value)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" : Permission denied", 2);
	exit(exit_value);
}
