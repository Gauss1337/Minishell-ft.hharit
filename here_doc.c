/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 22:58:14 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 06:12:55 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

void	wait_for_doc(pid_t pid)
{
	int	exits;

	signals3();
	waitpid(pid, &exits, 0);
	while (wait(0) > 0)
		;
	g_glob.errors = WEXITSTATUS(exits);
}

void	ft_doc(char *str, int fd)
{
	close(fd);
	free(str);
	exit(0);
}

void	here_doc(t_cmd *cmd)
{
	t_doc		doc;
	t_heredoc	*hd;

	doc.pid = fork();
	if (doc.pid == 0)
	{
		heredoc_signal();
		hd = (t_heredoc *)cmd;
		doc.temp = get_next_line(0);
		if (!doc.temp)
			exit(0);
		doc.line = ft_substr(doc.temp, 0, ft_strlen(doc.temp) - 1);
		free(doc.temp);
		while (ft_strcmp(doc.line, hd->delim))
		{
			write(hd->open_file, doc.line, ft_strlen(doc.line));
			write(hd->open_file, "\n", 1);
			doc.temp = get_next_line(0);
			free(doc.line);
			doc.line = ft_substr(doc.temp, 0, ft_strlen(doc.temp) - 1);
			free(doc.temp);
		}
		ft_doc(doc.line, hd->open_file);
	}
	wait_for_doc(doc.pid);
}
