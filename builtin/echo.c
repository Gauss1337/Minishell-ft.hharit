/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:54:49 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/10 18:13:50 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **str)
{
	int	i;
	int	newline;

	i = 0;
	newline = 0;
	if (!(*str))
		ft_putchar_fd('\n', 1);
	else
	{
		if (!ft_strncmp(str[i], "-n", 3))
		{
			newline = 1;
			i++;
		}
		while (str[i] != NULL)
		{
			ft_putstr_fd(str[i], 1);
			if (str[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
			i++;
		}
		if (!newline)
			ft_putchar_fd('\n', 1);
	}
}
