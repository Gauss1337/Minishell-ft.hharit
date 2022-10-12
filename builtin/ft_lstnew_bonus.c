/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <hharit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:54:24 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 07:19:12 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*htr;

	htr = ft_calloc (sizeof(t_list), 1);
	if (!htr)
		return (NULL);
	htr->next = NULL;
	htr->content = content;
	return (htr);
}
