/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:34 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/10 18:15:48 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(void)
{
	char	path [1024];

	if (getcwd(path, sizeof(path)) == NULL)
		return ;
	ft_putstr_fd(getcwd(path, sizeof(path)), 1);
	ft_putchar_fd('\n', 1);
}
