/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:55:32 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/16 03:27:36 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_glob	g_glob;

int	check_exp(char *str, t_list *envt)
{
	if (!(str) || *str == '#')
	{
		export_only(envt);
		return (1);
	}
	return (0);
}

int	check_double(t_list	**envt, char *str)
{
	t_list	*head;
	t_list	*prev;
	char	*s;
	char	*ptr;

	prev = NULL;
	head = *envt;
	s = get_right_name(str);
	while (head && ft_strncmp(head->content, s, ft_strlen(s)))
	{
		head = head->next;
	}
	if (head)
	{
		ptr = head->content;
		head->content = ft_strdup(str);
		free(ptr);
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

int	check_syntax(char *check)
{
	int	i;

	i = 0;
	while (check[i])
	{
		if (check[i] == '(' || check[i] == ')')
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putchar_fd(check[i], 2);
			ft_putendl_fd("'", 2);
			g_glob.errors = 258;
			return (0);
		}
		i++;
	}
	return (1);
}

void	export(t_list	**envt, char **str)
{
	int		i;
	char	*new;
	char	*check;

	i = -1;
	if (check_exp(*str, *envt))
		return ;
	while (str[++i])
	{	
		new = ret_exp(str[i]);
		check = ret_str(str[i], new);
		if (!valid_string(check, "export: `"))
		{
			free(check);
			return ;
		}
		else if (!check_syntax(check))
		{
			free(check);
			return ;
		}
		if (!check_double(envt, str[i]))
			ft_lstadd_back(envt, ft_lstnew(ft_strdup(str[i])));
		free(check);
	}
}
