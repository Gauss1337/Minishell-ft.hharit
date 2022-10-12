/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 01:54:13 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 08:24:44 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_cmd(void)
{
	t_exec	*cmd;

	cmd = (t_exec *)ft_calloc(1, sizeof(t_exec));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipe_data(t_cmd *right, t_cmd *left)
{
	t_pipe	*pipe;

	pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	pipe->type = PIPE;
	pipe->right = right;
	pipe->left = left;
	return ((t_cmd *)pipe);
}

t_redir	*redir_data(char *file, int flags, int fd, t_list *env_l)
{
	t_redir	*re_cmd;

	re_cmd = (t_redir *)ft_calloc(1, sizeof(t_redir));
	re_cmd->type = REDIR;
	re_cmd->file = verify(file, env_l);
	re_cmd->file = file;
	re_cmd->fd = fd;
	re_cmd->flags = flags;
	return (re_cmd);
}

char	*random_name(void)
{
	int		fd;
	char	*buf;

	fd = open("/dev/random", O_RDONLY, 0644);
	buf = (char *)malloc(sizeof(char) * 5);
	if (read(fd, buf, 5))
		return (buf);
	else
		return (NULL);
}

t_heredoc	*heredoc_data(char *file, int flags, int fd)
{
	t_heredoc	*re_cmd;

	re_cmd = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	re_cmd->type = HEREDOC;
	re_cmd->delim = file;
	re_cmd->fd = fd;
	re_cmd->flags = flags;
	re_cmd->file = file;
	re_cmd->file = ft_strjoin6("/tmp/", file);
	re_cmd->open_file = open(re_cmd->file, re_cmd->flags, 0644);
	here_doc((t_cmd *)re_cmd);
	return (re_cmd);
}
