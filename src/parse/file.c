/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:47 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 16:19:19 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "util/util.h"
#include "parse/parse.h"
#include "def.h"
#include "obj.h"

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

static t_obj_parser	get_obj_parser(char const **line)
{
	size_t				i;
	const char *const	types[OBJ_QTY] = {ID_A_LIGHT, ID_CAMERA,
		ID_LIGHT, ID_SPHERE, ID_PLANE, ID_CYLINDER};
	const t_obj_parser	funcs[OBJ_QTY] = {parse_a_light, parse_camera,
		parse_light, parse_sphere, parse_plane, parse_cylinder};

	i = 0;
	while (i < OBJ_QTY)
	{
		if (is_type(line, types[i]))
			return (funcs[i]);
		++i;
	}
	return (NULL);
}

static void	parse_line(char *line, int *err, t_scene *scene)
{
	skip_spaces((const char **) &line);
	get_obj_parser((const char **) &line)(line, err, scene);
}

int	parse_file(char const *path, t_scene *scene)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;
	int			err;

	if (fd == ERROR)
		return (ERROR);
	err = SUCCESS;
	(*scene) = (t_scene) {0};
	while (err != ERROR)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		parse_line(line, &err, scene);
		free(line);
		if (err == ERROR)
		{
			free_scene(scene);
			break ;
		}
	}
	close(fd);
	return (err);
}
