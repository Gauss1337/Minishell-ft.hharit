/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 03:40:16 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/15 02:49:13 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_symbol(char *str, char *stre, char *symbol)
{
	if (!str)
		return (0);
	while (str < stre && !ft_strchr(symbol, *str))
		str++;
	return (str < stre && ft_strchr(symbol, *str));
}

int	is_symbol(char *str, char *stre, char *symbol)
{
	char	*spaces;

	spaces = " \t\r\n\f\v";
	while (str < stre && ft_strchr(spaces, *str))
		str++;
	return (*str && ft_strchr(symbol, *str));
}

int	len_str(char *str, char *stre)
{
	int	len;

	len = 0;
	while (&str[len] < stre)
		len++;
	return (len);
}

char	*ret_str(char *str, char *stre)
{
	char	*f_str;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (!stre)
		return (str);
	f_str = (char *)malloc(sizeof(char) * (len_str(str, stre) + 1));
	while (str < stre)
	{
		f_str[i++] = *str;
		str++;
	}
	f_str[i] = '\0';
	return (f_str);
}

int	special_char(char c)
{
	if (c && ft_strchr("|;&+*()<>", c))
	{
		if (c == '+')
		{
			ft_putendl_fd("syntax error near unexpected token '>>'", 2);
			return (1);
		}
		else if (c == '*')
		{
			ft_putendl_fd("syntax error near unexpected token '<<'", 2);
			return (1);
		}			
		else if (c)
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			ft_putchar_fd(c, 2);
			ft_putendl_fd("'", 2);
			return (1);
		}
	}
	return (0);
}
