/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <hharit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:29:54 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/08 18:47:21 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*l1;

	l1 = *lst;
	if (!lst)
		*lst = new;
	if (lst != NULL)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (l1->next != NULL)
				l1 = l1->next;
			l1->next = new;
		}
	}
}
