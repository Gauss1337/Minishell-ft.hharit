/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:30:46 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 05:48:15 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_exec *ecmd, char **env, t_list **env_l, int built)
{
	if (!(*ecmd->args))
		exit(0);
	check_cmd(ecmd->args[0], 0);
	check_builtin(ecmd, env, env_l, built);
	execve(comd(env, ecmd), ecmd->args, env);
	if (*ecmd->args[0])
	{
		printf("command not found : %s\n", ecmd->args[0]);
		exit(127);
	}
}

void	exec_b(t_exec *ecmd, char **envp, t_list **env_l)
{
	if (!(*ecmd->args))
		return ;
	if (!ft_strcmp(ecmd->args[0], "unset"))
		unset(env_l, &ecmd->args[1], envp);
	else if (!ft_strcmp(ecmd->args[0], "exit"))
		ft_exit(&ecmd->args[1]);
	else if (!ft_strcmp(ecmd->args[0], "export"))
		export(env_l, &ecmd->args[1]);
	else if (!ft_strcmp(ecmd->args[0], "cd"))
		cd(ecmd->args[1]);
}
