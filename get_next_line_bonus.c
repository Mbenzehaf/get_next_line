/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 03:48:06 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/11/09 23:52:44 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*get_rest(char *str)
{
	char	*rest;
	int		i;
	int		len;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	len = ft_strlen(str + i + 1);
	rest = malloc(len + 1);
	if (!rest)
		return (NULL);
	while (str[i])
		rest[j++] = str[++i];
	free(str);
	return (rest);
}

char	*first_line(char *s)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen_n(s, '\n');
	str = malloc(len + 2);
	if (!str)
		return (NULL);
	while (s[i] && i < len + 1)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*read_line(char *buff, int fd)
{
	char	*str;
	int		check;

	check = 1;
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	while (!ft_strfind(buff) && check)
	{
		check = read(fd, str, BUFFER_SIZE);
		if (check == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		str[check] = 0;
		buff = ft_strjoin(buff, str);
		if (!*buff)
			break ;
	}
	free(str);
	str = NULL;
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff[fd])
		buff[fd] = ft_strdup("");
	buff[fd] = read_line(buff[fd], fd);
	if (!buff[fd] || !*buff[fd])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	str = first_line(buff[fd]);
	buff[fd] = get_rest(buff[fd]);
	return (str);
}
