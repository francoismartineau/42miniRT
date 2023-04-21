/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:04:34 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/21 17:13:51 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "context.h"
#include "raycast.h"
#include "math/math.h"
#include "math/mat3.h"
#include "math/vecmath.h"
#include "obj.h"

typedef struct s_data
{
	FPR		dist;
	t_vec3	normal;
	t_vec3	light;
	FPR		diffuse;
	t_vec3	view;
	t_vec3	reflected;
	FPR		spec;
}	t_data;

static void	desaturate(int color[3], FPR total)
{
	FPR	desat;

	desat = powf(total, 5);
	color[0] += (255 - color[0]) * desat;
	color[1] += (255 - color[1]) * desat;
	color[2] += (255 - color[2]) * desat;
}

static int	shade_sphere(const t_sphere *sphere, const t_vec3 hit,
	const t_context *ctx)
{
	const t_data	data = {
		.dist = fmaxf(powf(vec3_length(vec3_sub(hit, ctx->scene.lights[0].pos))
				+ 1.0f, 2.0f) - 1.0f, 2.0f),
		.normal = vec3_norm(vec3_sub(hit, sphere->pos)),
		.light = vec3_norm(vec3_sub(ctx->scene.lights[0].pos, hit)),
		.diffuse = clamp(vec3_dot(data.normal, data.light)
			/ data.dist, 0.0f, 1.0f),
		.view = vec3_norm(vec3_sub(ctx->scene.camera.pos, hit)),
		.reflected = vec3_reflect(vec3_scale(data.light, -1.0f), data.normal),
		.spec = powf(clamp(vec3_dot(data.view, data.reflected), 0.0f, 1.0f), 32.0f)
		/ data.dist
	};
	FPR				total;
	int				color[3];

	total = fminf(ctx->scene.a_light.ratio + data.diffuse + data.spec, 1.0f);
	color[0] = sphere->color.x * total * 0xff;
	color[1] = sphere->color.y * total * 0xff;
	color[2] = sphere->color.z * total * 0xff;
	desaturate(color, total);
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | 0xff);
}

static t_vec3	cyl_normal(const t_cylinder *cy, const t_vec3 hit)
{
	t_vec3	normal;
	t_vec3	proj;
	t_vec3	proj2;
	const t_vec3	oc = vec3_scale(cy->axis, cy->height / 2.0f);

	proj = vec3_scale(cy->axis, vec3_dot(cy->axis, vec3_sub(hit, oc)));
	proj2 = vec3_sub(hit, vec3_add(oc, proj));
	normal = vec3_norm(vec3_sub(hit, vec3_add(oc, proj)));
	return (normal);
}

static int	shade_cylinder(const t_cylinder *cy,
	const t_vec3 hit, const t_context *ctx)
{
	
	const t_data	data = {
		.dist = fmaxf(powf(vec3_length(vec3_sub(hit, ctx->scene.lights[0].pos))
				+ 1.0f, 2.0f) - 1.0f, 2.0f),
		.normal = cyl_normal(cy, hit),
		.light = vec3_norm(vec3_sub(ctx->scene.lights[0].pos, hit)),
		.diffuse = clamp(vec3_dot(data.normal, data.light)
			/ data.dist, 0.0f, 1.0f),
		.view = vec3_norm(vec3_sub(ctx->scene.camera.pos, hit)),
		.reflected = vec3_reflect(vec3_scale(data.light, -1.0f), data.normal),
		.spec = powf(clamp(vec3_dot(data.view, data.reflected), 0.0f, 1.0f), 32.0)
		/ data.dist
	};
	// const t_data	data = {
	// 	.dist = fmax(vec3_length(vec3_sub(rothit, ctx->scene.lights[0].pos))
	// 		* 2.0, 1.0),
	// 	.normal = cyl_normal(cy, rothit),
	// 	.light = vec3_norm(vec3_sub(ctx->scene.lights[0].pos, rothit)),
	// 	.diffuse = clamp(vec3_dot(data.normal, data.light) / data.dist,
	// 		0.0, 2.0),
	// 	.view = vec3_norm(vec3_sub(ctx->scene.camera.pos, rothit)),
	// 	.reflected = vec3_reflect(vec3_scale(data.light, -1.0), data.normal),
	// 	.spec = pow(clamp(vec3_dot(data.view, data.reflected), 0.0, 1.0), 32.0)
	// 	/ data.dist
	// };
	FPR				total;
	int				color[3];

	total = fminf(ctx->scene.a_light.ratio + data.diffuse + data.spec, 1.0f);
	color[0] = cy->color.x * total * 0xff;
	color[1] = cy->color.y * total * 0xff;
	color[2] = cy->color.z * total * 0xff;
	desaturate(color, total);
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | 0xff);
}

int	shade(const t_obj *obj, t_vec3 hit, const t_context *ctx)
{
	if (obj->type == e_sphere)
		return (shade_sphere(&obj->sphere, hit, ctx));
	else if (obj->type == e_cylinder)
	{
		return (shade_cylinder(&obj->cylinder, hit, ctx));
	}
	return (0xff);
}
