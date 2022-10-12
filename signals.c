/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:25:56 by hharit            #+#    #+#             */
/*   Updated: 2022/09/11 10:40:14 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, sig_handl) == SIG_ERR)
		exit(1);
}

void	signals2(void)
{
	if (signal(SIGINT, sig_handle) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}

void	heredoc_signal(void)
{
	if (signal(SIGINT, ctrl_handler) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit(1);
}

void	signals3(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
