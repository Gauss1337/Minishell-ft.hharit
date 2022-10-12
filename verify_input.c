/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:15:09 by hharit            #+#    #+#             */
/*   Updated: 2022/09/16 04:35:48 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	which_symbol(char *str, char *stre)
{
	while (str < stre)
	{
		if (ft_strchr("\"'$", *str))
			return (*ft_strchr("\"'$", *str));
		str++;
	}
	return (0);
}

char	*stop(char **str, char symbol)
{
	char	*stop;
	char	*new;
	int		i;

	i = 0;
	stop = ft_strchr(*str, symbol);
	if (*str < stop)
	{
		new = ret_str(*str, stop);
		*str = stop;
		return (new);
	}
	return (NULL);
}

char	*something(char **str, char symbol, t_list *env_l)
{
	char	*new;

	new = NULL;
	if (symbol == '"' || symbol == '\'')
		new = str_quotes(str, symbol, env_l);
	else if (symbol == '$')
		new = str_dollar(str, env_l);
	return (new);
}
