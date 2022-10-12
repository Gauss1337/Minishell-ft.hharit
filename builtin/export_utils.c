/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 17:20:30 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 08:27:32 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_glob	g_glob;

int	valid_string(char *str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			i++;
		else if (!is_variable(str[i]) || ft_isdigit(str[0]))
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(str, 2);
			ft_putendl_fd("=': not a valid identifier", 2);
			g_glob.errors = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*ret_exp(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '=')
			break ;
		str++;
	}
	return (str);
}

void	export_only(t_list	*env)
{
	while (env)
	{
		printf("declare -x %s\n", env->content);
		env = env->next;
	}
}

char	*get_right_name(char *str)
{
	char	*s1;
	char	*check;
	char	*new;

	s1 = ret_exp(str);
	check = ret_str(str, s1);
	new = ft_strjoin2(check, "=");
	return (new);
}
