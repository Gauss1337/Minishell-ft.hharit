/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:28 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 07:39:15 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	display_env(t_list *list)
{
	if (!list)
		return ;
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

t_list	*env(t_list *list, char **envt)
{
	int	i;

	i = 0;
	list = ft_lstnew(ft_strdup(envt[i]));
	i = 1;
	while (envt[i] != NULL)
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(envt[i])));
		i++;
	}
	return (list);
}
