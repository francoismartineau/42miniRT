/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:19:57 by francoma          #+#    #+#             */
/*   Updated: 2023/11/09 16:25:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "parse/parse.h"
#include "util/util.h"
#include "math/mat3.h"
#include "math/vecmath.h"
#include "obj.h"
#include "def.h"

void	parse_a_light(char const *line, int *err, t_scene *scene)
{
	float	ratio;

	if (*err == ERROR)
		return ;
	ratio = parse_double(&line, err, positive_normalized);
	parse_color(scene->a_light.color.e, &line, err);
	scene->a_light.color.e[0] *= ratio;
	scene->a_light.color.e[1] *= ratio;
	scene->a_light.color.e[2] *= ratio;
}

void	parse_camera(char const *line, int *err, t_scene *scene)
{
	if (*err == ERROR)
		return ;
	parse_vec(scene->camera.pos.e, &line, err, any);
	parse_vec(scene->camera.ori.e, &line, err, signed_normalized);
	scene->camera.fov = (float)parse_uint(&line, err, in_fov_range);
	scene->camera.ori = vec3_norm(scene->camera.ori);
	scene->camera.rot = lookvector(scene->camera.ori);
	scene->camera.fov *= M_PI / 180.0f;
}

void	parse_light(char const *line, int *err, t_scene *scene)
{
	t_light	*res;
	float	ratio;

	if (*err == ERROR)
		return ;
	res = ft_malloc(sizeof(*res) * (scene->lightc + 1));
	parse_vec(res[scene->lightc].pos.e, &line, err, any);
	ratio = parse_double(&line, err, positive_normalized);
	parse_color(res[scene->lightc].color.e, &line, err);
	res[scene->lightc].color.e[0] *= ratio;
	res[scene->lightc].color.e[1] *= ratio;
	res[scene->lightc].color.e[2] *= ratio;
	if (*err == ERROR)
	{
		ft_free((void **) &res);
		return ;
	}
	memcopy(res, scene->lights, sizeof(*scene->lights) * scene->lightc);
	ft_free((void **) &scene->lights);
	scene->lights = res;
	++scene->lightc;
}

void	parse_sphere(char const *line, int *err, t_scene *scene)
{
	t_obj	*res;

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
