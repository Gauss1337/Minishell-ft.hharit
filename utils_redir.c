/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 18:06:53 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 07:31:14 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_file(t_redir *rcmd)
{
	DIR	*dir;
	int	fd;

	rcmd->open_file = open(rcmd->file, rcmd->flags, 0644);
	if (rcmd->fd)
	{
		dir = opendir(rcmd->file);
		if (dir)
			is_dir(rcmd->file, dir, 1);
	}
	if (rcmd->open_file < 0)
	{
		fd = open(rcmd->file, rcmd->flags | O_CREAT | O_EXCL, 0644);
		if (fd < 0)
			perm_denied(rcmd->file, 1);
		else if (!rcmd->fd)
		{
			close(fd);
			unlink(rcmd->file);
			not_f_dir(rcmd->file, 1);
		}
	}
	rcmd->open_file = open(rcmd->file, rcmd->flags | O_CREAT, 0644);
}
