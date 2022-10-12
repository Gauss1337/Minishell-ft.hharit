/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 11:36:13 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 06:07:28 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_cmd(char **args, int *argc, char *str)
{
	*args = str;
	*argc = *argc + 1;
}

void	set_args(char *str, char **args, int *argc)
{
	if (str)
	{
		if (*str)
			input_cmd(args, argc, str);
		else
			free(str);
	}
}

t_cmd	*parse_exec(char **str, char *stre, t_list *env_l)
{
	t_exec	*ecmd;
	t_cmd	*cmd;
	char	*p;
	char	*pe;

	ecmd = (t_exec *)get_cmd();
	ecmd->argc = 0;
	cmd = (t_cmd *)ecmd;
	cmd = parse_redirs(cmd, str, stre, env_l);
	while (!is_symbol(*str, stre, "|"))
	{
		if (get_token(str, stre, &p, &pe) == 0)
			break ;
		else
			set_args(verify(ret_str(p, pe), env_l),
				&ecmd->args[ecmd->argc], &ecmd->argc);
		cmd = parse_redirs(cmd, str, stre, env_l);
	}
	ecmd->args[ecmd->argc] = 0;
	return ((t_cmd *)ecmd);
}
