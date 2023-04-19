/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:22:56 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 15:02:52 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#define ERROR -1

static ssize_t	buff_get_line(int fd, char **buff)
{
	ssize_t	rc;
	char	*temp_buff;

	temp_buff = ft_malloc(sizeof(*temp_buff) * (BUFFER_SIZE + 1));
	if (!temp_buff)
		return (ERROR);
	rc = 1;
	while (rc > 0 && !strchar(*buff, '\n'))
	{
		rc = read(fd, temp_buff, BUFFER_SIZE);
		if (rc < 0)
			break ;
		temp_buff[rc] = '\0';
		*buff = append_buff(*buff, temp_buff);
		if (!*buff)
			break ;
	}
	if (!*buff)
		rc = ERROR;
	ft_free((void **) &temp_buff);
	return (rc);
}

static char	*copy_line(char *buff)
{
	char	*line;
	size_t	i;

	i = 0;
	while (buff[i] && (!i || buff[i - 1] != '\n'))
		i++;
	line = ft_malloc(sizeof(*line) * (i + 1));
	if (!line)
	{
		ft_free((void **) &buff);
		return (NULL);
	}
	line[i] = '\0';
	ft_memmove(line, buff, i);
	return (line);
}

static int	buff_rm_line(char **buff, char *line)
{
	char	*new_buff;
	size_t	begin;
	size_t	len;

	begin = strln(line);
	len = strln(*buff + begin);
	if (!len)
		new_buff = NULL;
	else
	{
		new_buff = ft_malloc(sizeof(*new_buff) * (get_buff_mem_size(len + 1)));
		if (!new_buff)
		{
			ft_free((void **) &line);
			ft_free((void **) buff);
			return (ERROR);
		}
		ft_memmove(new_buff, *buff + begin, len);
		new_buff[len] = '\0';
	}
	ft_free((void **) buff);
	*buff = new_buff;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE < 1 || fd >= OPEN_MAX)
		return (buff[fd] = NULL);
	if (read(fd, NULL, 0)
		||ERROR == buff_get_line(fd, &buff[fd]) || (!buff[fd][0]))
	{
		ft_free((void **) &buff[fd]);
		return (buff[fd] = NULL);
	}
	line = copy_line(buff[fd]);
	if (!line)
		return (buff[fd] = NULL);
	if (ERROR == buff_rm_line(&buff[fd], line))
		return (buff[fd] = NULL);
	return (line);
}
