/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:25 by francoma          #+#    #+#             */
/*   Updated: 2023/04/13 15:57:18 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

t_obj	*parse_plane(char const *line, int *err)
{
	t_obj	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_plane;
	parse_vec(res->plane.coord, &line, err, any);
	parse_vec(res->plane.ori, &line, err, signed_normalized);
	res->plane.color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

t_obj	*parse_cylinder(char const *line, int *err)
{
	t_obj	*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	res->type = e_cylinder;
	parse_vec(res->cylinder.coord, &line, err, any);
	parse_vec(res->cylinder.axis, &line, err, signed_normalized);
	res->cylinder.diam = parse_double(&line, err, positive);
	res->cylinder.height = parse_double(&line, err, positive);
	res->cylinder.color = parse_color(&line, err);
	if (*err == ERROR)
		return (ft_free((void **) &res));
	return (res);
}

void	free_objs(t_obj **objs)
{
	size_t	i;

	i = 0;
	while (objs && objs[i])
	{
		free(objs[i]);
		++i;
	}
	free(objs);
}
