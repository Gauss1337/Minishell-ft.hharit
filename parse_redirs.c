/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:32:23 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/13 22:29:42 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

int	redir_error(int tok)
{
	if (special_char(tok))
	{
		g_glob.errors = 258;
		return (1);
	}
	if (!tok)
	{
		g_glob.errors = 258;
		ft_putendl_fd("syntax error near unexpected token '\\n'", 2);
		return (1);
	}
	return (0);
}

t_cmd	*reverse_cmd(t_cmd *cmd1, t_cmd *cmd2)
{
	t_redir		*rcmd;
	t_exec		*ecmd;
	t_heredoc	*hd;

	if (cmd1->type == REDIR)
	{
		rcmd = (t_redir *)cmd1;
		rcmd->cmd = cmd2;
		return (rcmd->cmd);
	}
	else if (cmd1->type == HEREDOC)
	{
		hd = (t_heredoc *)cmd1;
		hd->cmd = cmd2;
		return (hd->cmd);
	}
	else if (cmd1->type == EXEC)
	{
		ecmd = (t_exec *)cmd1;
		ecmd->cmd = cmd2;
		return (ecmd->cmd);
	}
	return (cmd2);
}

t_cmd	*parse_redirs(t_cmd *cmd, char **str, char *stre, t_list *env_l)
{
	char		*p;
	char		*pe;
	int			tok;
	t_redir		*rcmd;
	t_heredoc	*hd;

	while (is_symbol(*str, stre, "<>"))
	{
		tok = get_token(str, stre, 0, 0);
		if (redir_error(get_token(str, stre, &p, &pe)))
			return (NULL);
		if (tok == '>')
			rcmd = redir_data(ret_str(p, pe), O_WRONLY | O_TRUNC, 1, env_l);
		else if (tok == '<')
			rcmd = redir_data(ret_str(p, pe), O_RDONLY, 0, env_l);
		else if (tok == '+')
			rcmd = redir_data(ret_str(p, pe), O_RDWR | O_APPEND, 1, env_l);
		else if (tok == '*')
			hd = heredoc_data(ret_str(p, pe), O_CREAT | O_RDWR | O_TRUNC, 1);
		if (ft_strchr("<>+", tok))
			cmd = reverse_cmd(cmd, (t_cmd *)rcmd);
		else if (tok == '*')
			cmd = reverse_cmd(cmd, (t_cmd *)hd);
	}
	return (cmd);
}
