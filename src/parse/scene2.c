/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:25 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 16:29:15 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

void	parse_plane(char const *line, int *err, t_scene *scene)
{
	t_obj	*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res));
	res->type = e_plane;
	parse_vec(res->plane.pos.e, &line, err, any);
	parse_vec(res->plane.ori.e, &line, err, signed_normalized);
	parse_vec(res->plane.color.e, &line, err, is_uchar);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->objs = (t_obj **) append_scene((void **) scene->objs, res, sizeof(*res));
}

void	parse_cylinder(char const *line, int *err, t_scene *scene)
{
	t_obj	*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res));
	res->type = e_cylinder;
	parse_vec(res->cylinder.pos.e, &line, err, any);
	parse_vec(res->cylinder.axis.e, &line, err, signed_normalized);
	res->cylinder.rad = parse_double(&line, err, positive) / 2;
	res->cylinder.height = parse_double(&line, err, positive);
	parse_vec(res->cylinder.color.e, &line, err, is_uchar);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->objs = (t_obj **) append_scene((void **) scene->objs, res, sizeof(*res));
}

void	**append_scene(void **src, void *new, size_t size)
{
	size_t	len;
	void	**res;

	if (!new)
		return (src);
	len = 0;
	while (src && src[len])
		++len;
	res = ft_malloc(size * (len + 2));
	res[len + 1] = NULL;
	res[len] = new;
	memcopy(res, src, size * len);
	free(src);
	return (res);
}

void	free_scene(t_scene *scene)
{
	size_t	i;

	i = -1;
	while (scene->lights[++i])
		scene->lights[i] = ft_free((void *) &scene->lights[i]);
	i = -1;
	while (scene->objs[++i])
		scene->objs[i] = ft_free((void *) &scene->lights[i]);
}
