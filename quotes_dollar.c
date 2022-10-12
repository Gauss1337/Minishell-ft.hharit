/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 04:35:37 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 05:34:50 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_free(char *str)
{
	if (str && *str)
		free(str);
}

char	*verify(char *str, t_list *env_l)
{
	char	*stre;
	char	*ret;

	stre = str + ft_strlen(str);
	if (check_symbol(str, stre, "\"'$"))
	{
		ret = quotes_dollar(str, env_l);
		free(str);
		return (ret);
	}
	return (str);
}

void	rest(char *str, char *stre, char **new, char *join)
{
	if (join)
	{
		*new = join;
		check_free(join);
	}
	if (str < stre)
		*new = ft_strjoin2(*new, str);
}

char	*quotes_dollar(char *str, t_list *env_l)
{
	char	symbol;
	char	*new;
	char	*join;
	char	*s;
	char	*stre;

	join = NULL;
	s = NULL;
	new = NULL;
	stre = str + ft_strlen(str);
	while (check_symbol(str, stre, "\"'$"))
	{
		symbol = which_symbol(str, stre);
		s = stop(&str, symbol);
		new = something(&str, symbol, env_l);
		new = ft_strjoin5(s, new);
		join = ft_strjoin5(join, new);
	}
	rest(str, stre, &new, join);
	return (ft_strdup(new));
}
