/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:00:26 by adenhez           #+#    #+#             */
/*   Updated: 2020/11/22 15:02:53 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <string.h>

t_list	*new_list(int fd)
{
	t_list	*li;

	li = (t_list*)malloc(sizeof(t_list));
	if (li == NULL)
		return (NULL);
	li->fd = fd;
	li->storage = NULL;
	li->next = NULL;
	return (li);
}

char	*check_storage(char *storage, char **line)
{
	char *ptr;

	ptr = NULL;
	if (storage)
	{
		*line = ft_strdup(storage);
		ptr = ft_strchr(storage, '\n');
		if (ptr)
		{
			*ptr = 0;
			ft_strcpy(storage, ++ptr);
		}
		else
			ft_strclr(storage);
	}
	else
		*line = ft_strnew(BUFFER_SIZE);
	return (ptr);
}

int process(int fd, char **line, char **storage)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte;
	char	*latch;
	char	*temp;

	if ( (read(fd, buf, 0)) < 0)
		return (-1);
	latch  = check_storage(*storage, line);
	while (!latch && (byte = read(fd, buf , BUFFER_SIZE)))
	{
		buf[byte] = 0;
		latch = ft_strchr(buf, '\n');//latch retient l adresse memoire du char '\n' dans le buf
		if (latch != NULL)
		{
			*latch = 0;  // permet de couper net le buffer
			latch++;	
			//			printf("|PTR++ = %s|\n", ptr);
			*storage = ft_strdup(latch);
		}
		temp = *line;
		if(!(*line = ft_strjoin(*line, buf)) || (byte < 0))
			return (-1); // ajoute le buffer a line
		free(*temp);
	}
	if (byte || ft_strlen(*line) || ft_strlen(*storage))
		return (1);
	else
		return (0);
}


int	get_next_line(int fd, char **line)
{
	static t_list	*li;
	t_list			*temp;

	if(!line || fd < 0)
		return (-1); 
	if (li == NULL)
		li = new_list(fd);
	temp = li;
	while (temp->fd != fd)
	{
		if (temp->next == NULL)
			temp->next = new_list(fd);
		temp = temp->next;
	}
	return (process(temp->fd, line, &(temp->storage)));
}


int read_file(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	long		byte;

	while((byte =read(fd, buf , BUFFER_SIZE)))
	{
		printf("->%s\n", *line);
		buf[byte] = 0;
		*line = ft_strjoin(*line, buf);
	}
	return 0;
}

/*
#include <fcntl.h>
int	main(int argc, char **argv)
{

	(void) argc;
	int	fd;
	int	fd2;
	int	fd3;
	char *line;


	line = ft_strnew(BUFFER_SIZE);
	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	printf("[%d]\n", BUFFER_SIZE);
	while (get_next_line(fd, &line))
	{
		printf("____________________\n");
		printf("[%s]\n", line);
	}
	int k = 0;
	printf("____________________\n");
	get_next_line(fd3, &line);
	printf("[%s]\n", line);
	printf("____________________\n");
	get_next_line(fd, &line);
	printf("[%s]\n", line);
	printf("____________________\n");
	get_next_line(fd, &line);
	printf("[%s]\n", line);
	printf("____________________\n");
	get_next_line(fd3, &line);
	printf("[%s]\n", line);

	close(fd);
	return (0);
}

*/
