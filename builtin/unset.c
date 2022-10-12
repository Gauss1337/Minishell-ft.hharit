/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:37 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 05:55:05 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_last(t_list **head, t_list **ptr, char **str)
{
	t_list	*temp;

	temp = *head;
	(*ptr)->next = (*head)->next;
	free(temp->content);
	free(temp);
	free(*str);
}

void	new_list(t_list **list, char *str)
{
	t_list	*head;
	t_list	*ptr;

	ptr = NULL;
	head = *list;
	str = ft_strjoin6(str, "=");
	while (head && ft_strncmp(head->content, str, ft_strlen(str)))
	{	
		ptr = head;
		head = head->next;
	}
	if (!head)
	{
		free(str);
		return ;
	}
	else if (!ptr)
	{
		*list = (*list)->next;
		free(head->content);
		free(head);
		free(str);
	}
	else
		unset_last(&head, &ptr, &str);
}

void	unset(t_list **list, char **str, char **envp)
{
	int	i;

	if (!(*str))
		ft_putendl_fd("unset: not enough arguments", 2);
	if (!list || !*list)
		*list = env(*list, envp);
	i = 0;
	while (str[i])
	{
		if (!check_syntax(str[i]))
			return ;
		else if (!valid_string(str[i], "unset: `"))
			return ;
		new_list(list, str[i]);
		i++;
	}
}
