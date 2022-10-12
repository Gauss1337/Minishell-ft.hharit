/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:54:43 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 08:41:09 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(const char *str)
{
	if (!str)
	{
		if (!getenv("HOME"))
		{
			printf("HOME not set\n");
			return ;
		}
		chdir(getenv("HOME"));
		return ;
	}
	if (!chdir(str))
		return ;
	check_dir((char *)str);
}

void	check_dir(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" : Not a directory", 2);
		close(fd);
	}
}
