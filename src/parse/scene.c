/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 15:07:50 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parse/parse.h"
#include "util/util.h"
#include "scene.h"
#include "def.h"

void	parse_a_light(char const *line, int *err, t_scene *scene)
{
	if (*err == ERROR)
		return ;
	scene->a_light.ratio = parse_double(&line, err, positive_normalized);
	scene->a_light.color = parse_color(&line, err);
}

void	parse_camera(char const *line, int *err, t_scene *scene)
{
	if (*err == ERROR)
		return ;
	parse_vec(scene->camera.pos.e, &line, err, any);
	parse_vec(scene->camera.ori.e, &line, err, signed_normalized);
	scene->camera.fov = parse_uint(&line, err, in_fov_range);
}

void	parse_light(char const *line, int *err, t_scene *scene)
{
	t_light		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	parse_vec(res->pos.e, &line, err, any);
	res->ratio = parse_double(&line, err, positive_normalized);
	res->color = parse_color(&line, err);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->lights = append_scene(scene->lights, res, sizeof(*res));
}

void	parse_sphere(char const *line, int *err, t_scene *scene)
{
	t_obj		*res;

	if (*err == ERROR)
		return (NULL);
	res = ft_malloc(sizeof(*res));
	parse_vec(res->sphere.pos.e, &line, err, any);
	res->sphere.rad = parse_double(&line, err, positive) / 2.0;
	res->sphere.color = parse_color(&line, err);
	if (*err == ERROR)
		ft_free((void **) &res);
	else
		scene->objs = append_scene(scene->objs, res, sizeof(*res));
}
