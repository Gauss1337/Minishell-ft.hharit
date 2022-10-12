/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:24:12 by hharit            #+#    #+#             */
/*   Updated: 2022/09/15 03:22:18 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char **ptr, char *stre)
{
	char	q;
	char	*p;

	q = **ptr;
	p = *ptr;
	p++;
	while (p < stre && *p != q)
		p++;
	if (p < stre && *p == q)
		p++;
	*ptr = p;
}

char	*dollar_in_str(char *str, t_list *env_l)
{
	char	*ptr;
	char	*p;
	char	*stre;
	char	*dollar;
	char	*join;

	ptr = NULL;
	p = str;
	join = NULL;
	stre = str + ft_strlen(str);
	while (check_symbol(str, stre, "$"))
	{
		ptr = stop(&str, '$');
		dollar = str_dollar(&str, env_l);
		dollar = ft_strjoin5(ptr, dollar);
		join = ft_strjoin5(join, dollar);
	}
	dollar = join;
	if (str < stre)
		dollar = ft_strjoin2(dollar, str);
	free(p);
	return (dollar);
}

char	*str_quotes(char **str, char symbol, t_list *env_l)
{
	char	*ptr;
	char	*new;

	ptr = *str;
	ptr++;
	new = stop(&ptr, symbol);
	if (symbol == '"' && ft_strchr(new, '$'))
		new = dollar_in_str(new, env_l);
	if (*ptr == symbol)
		ptr++;
	*str = ptr;
	return (new);
}
