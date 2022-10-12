/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:43:58 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 08:48:07 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_handler(int sig)
{
	sig = 1;
	exit(1);
}

void	sig_handl(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}

void	sig_handle(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	exit_handle(int exits)
{
	ft_putendl_fd("exit", 1);
	exit(exits);
}
