/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:30 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/13 22:30:00 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_glob	g_glob;

int	tab_length(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	exit_check(char *list)
{
	int	ex;

	if (list)
	{
		ex = ft_atoi(list);
		exit (ex % 256);
	}
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || i >= 19)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **list)
{
	int	exit_value;

	exit_value = 0;
	ft_putendl_fd("exit", 1);
	if (list && *list)
	{
		if (!check_digit(*list))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(*list, 2);
			ft_putendl_fd(" :numeric argument required", 2);
			exit(255);
		}
		if (tab_length(list) > 1)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			g_glob.errors = 1;
			return ;
		}
		exit_check(*list);
		exit_value = ft_atoi(*list);
	}
	exit(exit_value);
}
