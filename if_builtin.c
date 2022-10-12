/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:17:05 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 01:34:20 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "pwd"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	return (0);
}

int	is_builtin_p(char *str)
{
	if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "exit"))
		return (1);
	else if (!ft_strcmp(str, "export"))
		return (1);
	else if (!ft_strcmp(str, "cd"))
		return (1);
	return (0);
}

void	check_builtin(t_exec *ecmd, char **envp, t_list **env_l, int built)
{
	if (built == 2 && is_builtin(ecmd->args[0]))
		exit(0);
	else if (!ft_strcmp(ecmd->args[0], "echo"))
		echo(&ecmd->args[1]);
	else if (!ft_strcmp(ecmd->args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(ecmd->args[0], "unset"))
		unset(env_l, &ecmd->args[1], envp);
	else if (!ft_strcmp(ecmd->args[0], "exit"))
		ft_exit(&ecmd->args[1]);
	else if (!ft_strcmp(ecmd->args[0], "export"))
		export(env_l, &ecmd->args[1]);
	else if (!ft_strcmp(ecmd->args[0], "env"))
		display_env(*env_l);
	else if (!ft_strcmp(ecmd->args[0], "cd"))
		cd(ecmd->args[1]);
	if (is_builtin(ecmd->args[0]))
		exit(0);
}

t_cmd	*exec_builtin(t_cmd	*cmd, char **envp, t_list **env_l, int *child)
{
	t_exec	*ecmd;

	if (g_glob.errors == 258)
	{
		*child = 0;
		return (cmd);
	}
	else if (cmd->type == PIPE || !check_errors(cmd))
	{
		*child = 1;
		return (cmd);
	}
	else if (cmd->type == EXEC && ((t_exec *)cmd)->args[0])
	{
		ecmd = (t_exec *)cmd;
		if (is_builtin_p(ecmd->args[0]))
		{
			*child = 2;
			exec_b(ecmd, envp, env_l);
			if (!ecmd->cmd)
				*child = 0;
		}
	}
	return (cmd);
}
