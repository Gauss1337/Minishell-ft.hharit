/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:29:16 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 05:49:36 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) \
				+ ft_strlen((const char *)s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	j = 0;
	while (s2[j] != '\0')
	{
		str[++i] = s2[j++];
	}
	str[++i] = '\0';
	return (str);
}

char	**path(char **envp)
{
	char	*htr;
	int		i;

	htr = NULL;
	i = 0;
	while (envp && envp[i]
		&& ft_strncmp(envp[i], "PATH=", 5) != 0)
			i++;
	return (ft_split(envp[i], ':'));
}

void	check_cmd(char *cmd, int c)
{
	DIR		*dir;
	char	*cmde;
	int		fd;

	cmde = cmd + ft_strlen(cmd);
	if (!c && !check_symbol(cmd, cmde, "/"))
		return ;
	dir = opendir(cmd);
	if (dir)
		is_dir(cmd, dir, 126);
	else
	{
		fd = open(cmd, O_RDWR | O_CREAT | O_EXCL, 0644);
		if (!check_symbol(cmd, cmde, "/") && fd < 0)
			perm_denied(cmd, 126);
		else
		{
			close(fd);
			unlink(cmd);
			not_f_dir(cmd, 127);
		}
	}
}

char	*comd(char **envp, t_exec *list)
{
	int		i;
	char	**paths;
	char	*tab;
	char	*join;

	paths = path(envp);
	if (!paths)
		check_cmd(list->args[0], 1);
	tab = NULL;
	if (!access(list->args[0], X_OK))
		return (list->args[0]);
	i = 0;
	while (paths[i] != NULL && *list->args[0])
	{
		join = ft_strjoin(paths[i], list->args[0]);
		if (!access(join, X_OK))
		{
			tab = ft_strdup(join);
			free(join);
			return (tab);
		}
		free(join);
		i++;
	}
	return (tab);
}
