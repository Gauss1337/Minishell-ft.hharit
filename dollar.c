/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:05:55 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 05:48:28 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_glob	g_glob;

int	is_variable(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ret_dollar(char *str)
{
	if (!str)
		return (NULL);
	if (ft_isdigit(str[0]))
		return (str + 1);
	while (*str && is_variable(*str))
		str++;
	return (str);
}

char	*var_env(char *str, t_list *env_l)
{
	char	*ptr;

	ptr = NULL;
	str = ft_strjoin2(str, "=");
	while (env_l)
	{
		if (!ft_strncmp(env_l->content, str, ft_strlen(str)))
		{
			ptr = env_l->content;
			ptr += ft_strlen(str);
			free(str);
			return (ft_strdup(ptr));
		}
		env_l = env_l->next;
	}
	free(str);
	return ("\0");
}

int	after_dollar(char **str, char **dollar)
{
	char	*ptr;

	ptr = *str + 1;
	if (*ptr == 48)
	{
		*dollar = ft_strdup("𝓂𝒾𝓃𝒾𝓈𝒽𝑒𝓁𝓁");
		*str = ptr + 1;
		return (1);
	}
	else if (*ptr == '?')
	{
		*dollar = ft_itoa(g_glob.exit);
		*str = ptr + 1;
		return (1);
	}
	else if (*ptr == '$')
	{
		*dollar = ft_strdup("PID");
		*str = ptr + 1;
		return (1);
	}
	return (0);
}

char	*str_dollar(char **str, t_list *env_l)
{
	char	*ptr;
	char	*ptre;
	char	*dollar;

	ptr = *str + 1;
	dollar = NULL;
	if (!*ptr)
	{
		*str = ptr;
		return (ft_strdup("$"));
	}
	else if (!after_dollar(str, &dollar))
	{
		ptre = ret_dollar(ptr);
		dollar = var_env(ret_str(ptr, ptre), env_l);
		*str = ptre;
	}
	return (dollar);
}
