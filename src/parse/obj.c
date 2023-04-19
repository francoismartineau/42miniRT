/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/04/19 09:25:15 by francoma         ###   ########.fr       */
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
	parse_color(scene->a_light.color.e, &line, err);
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
		return ;
	res = ft_malloc(sizeof(*res) * (scene->lightc + 1));
	parse_vec(res[scene->lightc].pos.e, &line, err, any);
	res[scene->lightc].ratio = parse_double(&line, err, positive_normalized);
	parse_color(res[scene->lightc].color.e, &line, err);
	if (*err == ERROR)
		return ;
	memcopy(res, scene->lights, sizeof(*scene->lights) * scene->lightc);
	free(scene->lights);
	scene->lights = res;
	++scene->lightc;
}

void	parse_sphere(char const *line, int *err, t_scene *scene)
{
	t_obj		*res;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res) * (scene->objc + 1));
	res[scene->objc].type = e_sphere;
	parse_vec(res[scene->objc].sphere.pos.e, &line, err, any);
	res[scene->objc].sphere.rad = parse_double(&line, err, positive) / 2.0;
	parse_color(res[scene->objc].sphere.color.e, &line, err);
	if (*err == ERROR)
		return ;
	append_obj(scene, res);
}
