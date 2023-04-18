/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:55:47 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 16:04:25 by francoma         ###   ########.fr       */
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

static t_obj	**append_objs(t_obj **objs, t_obj *new)
{
	size_t	len;
	t_obj	**res;

	if (!new)
		return (objs);
	len = 0;
	while (objs && objs[len])
		++len;
	res = ft_malloc(sizeof(*res) * (len + 2));
	res[len + 1] = NULL;
	res[len] = new;
	memcopy(res, objs, sizeof(*res) * len);
	free(objs);
	return (res);
}

t_obj	*parse_line(char *line, int *err)
{
	skip_spaces((const char **) &line);
	return (get_obj_parser((const char **) &line)(line, err));
}

t_obj	**parse_file(char const *path)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;
	int			err;
	t_obj		*obj;
	t_obj		**res;

	err = SUCCESS;
	res = NULL;
	while (err != ERROR)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		obj = parse_line(line, &err);
		free(line);
		if (err == ERROR)
		{
			free_objs(res);
			break ;
		}
		res = append_objs(res, obj);
	}
	close(fd);
	return (res);
}
