/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:04:34 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/29 20:32:05 by eboyce-n         ###   ########.fr       */
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

static t_vec3	getnormal(const t_obj *obj, const t_vec3 hit)
{
	t_vec3	proj;

	if (obj->type == e_sphere)
		return (vec3_norm(vec3_sub(hit, obj->sphere.pos)));
	else if (obj->type == e_plane)
		return (vec3_scale(obj->plane.ori, -1.0f));
	else
	{
		proj = vec3_sub(hit, obj->cylinder.pos);
		return (vec3_norm(vec3_sub(proj, vec3_scale(obj->cylinder.axis,
						vec3_dot(proj, obj->cylinder.axis)))));
	}
}

static void	desaturate(t_vec3 *color, FPR total)
{
	const FPR	desat = powf(total, 5);

	color->x += (1.0f - color->x) * desat;
	color->y += (1.0f - color->y) * desat;
	color->z += (1.0f - color->z) * desat;
}

static int	isobscured(const t_vec3 hit, const t_scene *s,
	const t_obj *obj, const t_light *l)
{
	const t_ray		ray = (t_ray){hit, vec3_sub(l->pos, hit)};
	FPR				t;
	size_t			i;

	i = -1;
	while (++i < s->objc)
	{
		if (s->objs + i == obj)
			continue ;
		t = ray_intersect(ray, s->objs + i);
		if (t > 0.0f && t < 0.999f)
			return (1);
	}
	return (0);
}

static t_vec3	shadelight(const t_obj *obj, const t_vec3 hit,
	const t_scene *s, const t_light *l)
{
	t_data		data;
	t_vec3		color;

	if (isobscured(hit, s, obj, l))
		return ((t_vec3){{{0.0f, 0.0f, 0.0f}}});
	data.dist = fmaxf(powf(vec3_length(vec3_sub(hit, l->pos)) + 1.0f, 2.0f)
			- 1.0f, 2.0f);
	data.normal = getnormal(obj, hit);
	data.light = vec3_norm(vec3_sub(l->pos, hit));
	data.diffuse = clamp(vec3_dot(data.normal, data.light)
			/ data.dist, 0.0f, 1.0f);
	data.view = vec3_norm(vec3_sub(s->camera.pos, hit));
	data.reflected = vec3_reflect(vec3_scale(data.light, -1.0f), data.normal);
	data.spec = powf(clamp(vec3_dot(data.view, data.reflected), 0.0f, 1.0f),
			32.0f) / data.dist;
	color = vec3_scale(obj->color, fminf(data.diffuse + data.spec, 1.0f));
	desaturate(&color, data.diffuse + data.spec);
	return (color);
}

int	shade(const t_obj *obj, const t_vec3 hit, const t_scene *s)
{
	t_vec3	color;
	size_t	i;

	color = s->a_light.color;
	i = -1;
	while (++i < s->lightc)
		color = vec3_add(color, shadelight(obj, hit, s, s->lights + i));
	color.x = fminf(color.x, 1.0f);
	color.y = fminf(color.y, 1.0f);
	color.z = fminf(color.z, 1.0f);
	return ((int)(color.x * 255.0f) << 24
		| (int)(color.y * 255.0f) << 16
		| (int)(color.z * 255.0f) << 8 | 0xff);
}
