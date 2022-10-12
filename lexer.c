/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <hharit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 03:02:20 by hharit            #+#    #+#             */
/*   Updated: 2022/09/05 21:19:34 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_append(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '>';
	if (**ptr == '>')
	{
		(*ptr)++;
		tok = '+';
	}
	return (tok);
}

int	check_herdoc(char **ptr)
{
	int	tok;

	(*ptr)++;
	tok = '<';
	if (**ptr == '<')
	{
		(*ptr)++;
		tok = '*';
	}
	return (tok);
}

int	token(char **ptr, char *stre, int tok)
{
	if (ft_strchr("|<>", tok))
	{
		if (tok == '>')
			tok = check_append(ptr);
		else if (tok == '<')
			tok = check_herdoc(ptr);
		else if (tok == '|')
			(*ptr)++;
	}
	else
	{
		while (*ptr < stre && !ft_strchr("\t\v\r\n\f ", **ptr)
			&& !ft_strchr("|<>", **ptr))
		{
			if (ft_strchr("'\"", **ptr))
				skip_quotes(ptr, stre);
			else
				(*ptr)++;
		}
	}
	return (tok);
}

int	get_token(char **str, char *stre, char **previous, char **ep)
{
	int		tok;
	char	*ptr;

	ptr = *str;
	while (ptr < stre && ft_strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	if (previous)
		*previous = ptr;
	tok = *ptr;
	if (!tok)
		return (0);
	tok = token(&ptr, stre, tok);
	if (ep)
		*ep = ptr;
	while (ptr < stre && ft_strchr("\t\v\r\n\f ", *ptr))
		ptr++;
	*str = ptr;
	return (tok);
}
