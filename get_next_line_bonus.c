/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:00:26 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/26 16:46:28 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	process(char **str, char **line)
{
	char	*temp;
	char	*ptr;
	int		len;

	len = 0;
	while ((*str)[len] != '\n' && (*str)[len] != 0)
		len++;
	ptr = ft_strchr(*str, '\n');
	if (ptr != NULL)
	{
		*line = ft_strsub(*str, 0, len);
		temp = ft_strdup(++ptr);
		if (temp == NULL)
			return (-1);
		free(*str);
		*str = temp;
	}
	else
	{
		if ((*line = ft_strdup(*str)) == NULL)
			return (-1);
		ft_strclr(str);
	}
	return (1);
}

int	output(int byte, char **str, char **line)
{
	if (byte < 0)
		return (-1);
	else if (byte == 0 && *str == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	else
	{
		if (process(&(*str), line) == -1)
			return (-1);
		if (*str == NULL)
			return (0);
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	int			byte;
	static char	*store[FD_MAX];
	char		*temp;
	char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || fd > FD_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((byte = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[byte] = 0;
		if (store[fd] == NULL)
			store[fd] = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(store[fd], buf);
			if (temp == NULL)
				return (-1);
			store[fd] = temp;
		}
		if (ft_strchr(store[fd], '\n'))
			break ;
	}
	if (byte < 0)
		return (-1);
	return (output(byte, &(store[fd]), line));
}
