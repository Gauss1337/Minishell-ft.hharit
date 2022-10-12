/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 01:53:31 by hharit            #+#    #+#             */
/*   Updated: 2022/09/13 22:29:35 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

t_cmd	*parse_pipe(char **str, char *stre, t_list *env_l)
{
	t_cmd	*cmd;

	cmd = parse_exec(str, stre, env_l);
	if (is_symbol(*str, stre, "|"))
	{
		if (!*((t_exec *)cmd)->args && !((t_exec *)cmd)->cmd)
		{
			ft_putendl_fd("syntax error near unexpected token '|'", 2);
			g_glob.errors = 258;
			return (NULL);
		}
		get_token(str, stre, 0, 0);
		cmd = pipe_data(cmd, parse_pipe(str, stre, env_l));
	}
	return (cmd);
}
