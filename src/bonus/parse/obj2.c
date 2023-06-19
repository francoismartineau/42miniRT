/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:19:25 by francoma          #+#    #+#             */
/*   Updated: 2023/06/19 11:14:09 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "math/vecmath.h"
#include "obj.h"
#include "def.h"

void	parse_plane(char const *line, int *err, t_scene *scene)
{
	t_obj	*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res) * (scene->objc + 1));
	res[scene->objc].type = e_plane;
	parse_vec(res[scene->objc].plane.pos.e, &line, err, any);
	parse_vec(res[scene->objc].plane.ori.e, &line, err, signed_normalized);
	res[scene->objc].plane.ori = vec3_norm(res[scene->objc].plane.ori);
	parse_color(res[scene->objc].plane.color.e, &line, err);
	if (*err == ERROR)
		return ;
	parse_color(res[scene->objc].emit.e, &line, err);
	if (*err == ERROR)
		res[scene->objc].emit = (t_vec3){{{0.0f, 0.0f, 0.0f}}};
	res[scene->objc].r = parse_double(&line, err, positive_normalized);
	if (*err == ERROR)
		res[scene->objc].r = 1.0f;
	*err = 0;
	append_obj(scene, res);
}

void	parse_cylinder(char const *line, int *err, t_scene *scene)
{
	t_obj	*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res) * (scene->objc + 1));
	res[scene->objc].type = e_cylinder;
	parse_vec(res[scene->objc].cylinder.pos.e, &line, err, any);
	parse_vec(res[scene->objc].cylinder.axis.e, &line, err, signed_normalized);
	res[scene->objc].cylinder.axis = vec3_norm(res[scene->objc].cylinder.axis);
	res[scene->objc].cylinder.rad = parse_double(&line, err, positive) / 2;
	res[scene->objc].cylinder.height = parse_double(&line, err, positive);
	parse_color(res[scene->objc].cylinder.color.e, &line, err);
	if (*err == ERROR)
		return ;
	parse_color(res[scene->objc].emit.e, &line, err);
	if (*err == ERROR)
		res[scene->objc].emit = (t_vec3){{{0.0f, 0.0f, 0.0f}}};
	res[scene->objc].r = parse_double(&line, err, positive_normalized);
	if (*err == ERROR)
		res[scene->objc].r = 1.0f;
	*err = 0;
	append_obj(scene, res);
}

void	append_obj(t_scene *scene, t_obj *new_alloc)
{
	memcopy(new_alloc, scene->objs, sizeof(*scene->objs) * scene->objc);
	ft_free((void **) &scene->objs);
	scene->objs = new_alloc;
	++scene->objc;
}

void	free_scene(t_scene *scene)
{
	ft_free((void **) &scene->lights);
	ft_free((void **) &scene->objs);
}
