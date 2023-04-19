/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:04:34 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/19 08:19:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "raycast.h"
#include "math/vecmath.h"
#include "obj.h"

static int	shade_sphere(const t_sphere *sphere, const t_vec3 hit, const t_context *ctx)
{
	t_vec3	normal;
	t_vec3	light;
	t_vec3	view;
	t_vec3	half;
	float	ambient;
	float	diffuse;
	float	specular;
	float	phong;

	normal = vec3_sub(hit, sphere->pos);
	normal = vec3_normalize(normal);
	light = vec3_sub(ctx->scene.lights[0]->pos, hit);
	light = vec3_normalize(light);
	view = vec3_sub(ctx->scene.camera.pos, hit);
	view = vec3_normalize(view);
	half = vec3_add(light, view);
	half = vec3_normalize(half);
	ambient = 0.1;
	diffuse = vec3_dot(light, normal);
	specular = vec3_dot(half, normal);
	phong = ambient + diffuse + specular;
	return ((int)(sphere->color.x * phong) << 24 |
		(int)(sphere->color.y * phong) << 16 |
		(int)(sphere->color.z * phong) << 8 | 0xff);
}

int	shade(const t_obj *obj, const t_vec3 hit, const t_context *ctx)
{
	if (obj->type == e_sphere)
		return (shade_sphere(&obj->sphere, hit, ctx));
	return (0xff);
}