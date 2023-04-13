/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:47 by francoma          #+#    #+#             */
/*   Updated: 2023/04/12 15:37:48 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "util/util.h"
#include "parse/parse.h"
#include "parse/parse_obj.h"
#include "def.h"

static int	is_type(char const **line, char const *type)
{
	int		res;
	size_t	len;

	len = strln(type);
	res = !strncmp(*line, type, len);
	if (res)
		*line += len;
	return (res);
}

void	parse_line(char const *line, int *err)
{
	skip_spaces(&line);
	if (is_type(&line, ID_A_LIGHT))
		parse_a_light(line, err);
	else if (is_type(&line, ID_CAMERA))
		parse_camera(line, err);
	else if (is_type(&line, ID_LIGHT))
		parse_light(line, err);
	else if (is_type(&line, ID_SPHERE))
		parse_sphere(line, err);
	else if (is_type(&line, ID_PLANE))
		parse_plane(line, err);
	else if (is_type(&line, ID_CYLINDER))
		parse_cylinder(line, err);
}

void	parse_file(char const *path)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;
	int			err;

	err = SUCCESS;
	while (err != ERROR)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(line, &err);
		free(line);
	}
	close(fd);
}
