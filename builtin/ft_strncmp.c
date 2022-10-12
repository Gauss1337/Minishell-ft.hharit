/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hharit <hharit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:25:09 by ahakam            #+#    #+#             */
/*   Updated: 2022/09/08 18:47:21 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*htr;
	size_t			i;

	i = 0;
	str = (unsigned char *)s1;
	htr = (unsigned char *)s2;
	if ((!s1 && !s2) || n == 0)
		return (0);
	while (str[i] == htr[i] && i < n - 1 && str[i] != '\0')
		i++;
	if (str[i] != htr[i])
		return (str[i] - htr[i]);
	return (str[i] - htr[i]);
}
