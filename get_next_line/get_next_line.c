/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 02:19:22 by ahakam            #+#    #+#             */
/*   Updated: 2022/08/25 22:47:42 by hharit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchr2(const char *s, int c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s);
	while (i < j && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*find_n(char **btr)
{
	char	*temp;
	char	*line;
	int		i;

	i = ft_strchr2(*btr, '\n');
	temp = *btr;
	line = ft_substr(*btr, 0, i + 1);
	*btr = ft_substr(*btr, i + 1, ft_strlen(*btr));
	free(temp);
	temp = NULL;
	return (line);
}

static char	*didnt_find_n(char **btr)
{
	char	*temp;

	if (**btr != '\0' && *btr != NULL)
	{
		temp = *btr;
		*btr = NULL;
		return (temp);
	}
	else
	{	
		free(*btr);
		*btr = NULL;
		return (NULL);
	}
}

char	*get_next_line(int fd)
{
	char				buffer[1 + 1];
	static char			*btr;
	char				*line;
	int					i;

	if (fd < 0)
		return (NULL);
	if (!btr)
		btr = ft_strdup("");
	while (ft_strchr2(btr, '\n') == -1)
	{
		i = read(fd, buffer, 1);
		if (i == 0 || i == -1)
			break ;
		buffer[i] = '\0';
		btr = ft_strjoin2(btr, buffer);
	}
	if (ft_strchr2(btr, '\n') == -1)
	{
		line = didnt_find_n(&btr);
		return (line);
	}
	line = find_n(&btr);
	return (line);
}
