/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 17:39:50 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "obj.h"
#include "def.h"

void	parse_a_light(char const *line, int *err, t_scene *scene)
{
	if (*err == ERROR)
		return ;
	scene->a_light.ratio = parse_double(&line, err, positive_normalized);
	parse_vec(scene->a_light.color.e, &line, err, is_uchar);
}

void	parse_camera(char const *line, int *err, t_scene *scene)
{
	if (*err == ERROR)
		return ;
	parse_vec(scene->camera.pos.e, &line, err, any);
	parse_vec(scene->camera.ori.e, &line, err, signed_normalized);
	scene->camera.fov = parse_uint(&line, err, in_fov_range);
}

#include <stdio.h>
void	parse_light(char const *line, int *err, t_scene *scene)
{
	t_light		*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res));
	parse_vec(res->pos.e, &line, err, any);
	printf("light: %f, %f, %f\n", res->pos.e[0], res->pos.e[1], res->pos.e[2]);
	res->ratio = parse_double(&line, err, positive_normalized);
	parse_color(res->color.e, &line, err);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->lights = (t_light **) append_scene((void **) scene->lights, res, sizeof(*res));
}

void	parse_sphere(char const *line, int *err, t_scene *scene)
{
	t_obj		*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res));
	parse_vec(res->sphere.pos.e, &line, err, any);
	res->sphere.rad = parse_double(&line, err, positive) / 2.0;
	parse_vec(res->sphere.color.e, &line, err, is_uchar);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->objs = (t_obj **) append_scene((void **) scene->objs, res, sizeof(*res));
}
