/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 00:29:45 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 08:54:59 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	g_glob;

t_cmd	*parsing(char **str, t_list *env_l)
{
	t_cmd	*cmd;
	char	*stre;

	stre = *str + ft_strlen(*str);
	cmd = parse_pipe(str, stre, env_l);
	return (cmd);
}

int	get_exits(int exit_status)
{
	if (g_glob.errors == 258 || g_glob.errors == 1)
	{
		g_glob.exit = g_glob.errors;
		g_glob.errors = 0;
	}
	else if (WIFSIGNALED(exit_status))
		g_glob.exit = WTERMSIG(exit_status) + 128;
	else
		g_glob.exit = WEXITSTATUS(exit_status);
	return (g_glob.exit);
}

char	**get_env(t_list *env_l, char **env_p)
{
	int	i;

	i = 0;
	env_p = malloc(sizeof(char *) * (ft_lstsize(env_l) + 1));
	while (env_l)
	{
		env_p[i] = ft_strdup(env_l->content);
		env_l = env_l->next;
		i++;
	}
	return (env_p);
}

void	minishell(t_cmd *cmd, char **env_p, t_list *env_l, int child)
{
	int	pid;
	int	exit;

	exit = 0;
	if (child > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			env_p = get_env(env_l, env_p);
			runcmd(cmd, env_p, child, &env_l);
		}
		signals();
		waitpid(pid, &exit, 0);
	}
	get_exits(exit);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env_p;
	t_par	list;
	t_cmd	*cmd;
	t_list	*env_l;

	env_l = NULL;
	env_p = NULL;
	env_l = env(env_l, envp);
	(void)argc, (void)argv;
	while (1)
	{
		list.child = 1;
		signals2();
		list.str = readline("🎀 𝓂𝒾𝓃𝒾𝓈𝒽𝑒𝓁𝓁 🎀: ");
		list.ptr = list.str;
		add_history(list.str);
		if (!list.str)
			exit_handle(g_glob.exit);
		cmd = exec_builtin(parsing(&list.ptr, env_l) \
				, envp, &env_l, &list.child);
		list.ptr = list.str;
		minishell(cmd, env_p, env_l, list.child);
		free(list.ptr);
	}
}
