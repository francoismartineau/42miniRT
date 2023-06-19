/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:04:34 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 12:22:25 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include "bonus/render/shading.h"
#include "math/math.h"
#include "math/mat3.h"
#include "math/vecmath.h"
#include "obj.h"

#define SAMPLE_DEPTH 16

typedef struct s_data
{
	FPR		dist;
	t_vec3	normal;
	t_vec3	light;
	FPR		diffuse;
	t_vec3	view;
	t_vec3	reflect;
	FPR		spec;
}	t_data;

static t_vec3	randnorm(const t_vec3 n, FPR r)
{
	t_vec3	v = (t_vec3){{{
			(rand() / (FPR)(RAND_MAX / 2) - 1.0f),
			(rand() / (FPR)(RAND_MAX / 2) - 1.0f),
			(rand() / (FPR)(RAND_MAX / 2) - 1.0f),
		}}};
	v = vec3_norm(v);
	if (vec3_dot(v, n) < 0.0f)
		v = vec3_scale(v, -1.0f);
	v.x = v.x * r + n.x * (1.0f - r);
	v.y = v.y * r + n.y * (1.0f - r);
	v.z = v.z * r + n.z * (1.0f - r);
	v = vec3_norm(v);
	return (v);
}

static t_vec3	getnormal(const t_obj *obj, const t_vec3 hit)
{
	t_vec3	proj;

	if (obj->type == e_sphere)
		return (vec3_norm(vec3_sub(hit, obj->sphere.pos)));
	else if (obj->type == e_plane)
		return (obj->plane.ori);
	else
	{
		proj = vec3_sub(hit, obj->cylinder.pos);
		return (vec3_norm(vec3_sub(proj, vec3_scale(obj->cylinder.axis,
						vec3_dot(proj, obj->cylinder.axis)))));
	}
}

// static t_vec3	desaturate(const t_vec3 color, FPR total)
// {
// 	const FPR		desat = powf(total, 5);

// 	return ((t_vec3){{{
// 				color.x + (1.0f - color.x) * desat,
// 				color.y + (1.0f - color.y) * desat,
// 				color.z + (1.0f - color.z) * desat,
// 			}}});
// }

// static int	isobscured(const t_vec3 hit, const t_scene *s,
// 	const t_obj *obj, const t_light *l)
// {
// 	const t_ray		ray = (t_ray){l->pos, vec3_sub(hit, l->pos)};
// 	FPR				t;
// 	size_t			i;

// 	i = -1;
// 	while (++i < s->objc)
// 	{
// 		if (s->objs + i == obj)
// 			continue ;
// 		t = ray_intersect(ray, s->objs + i);
// 		if (t > 0.0f && t < 0.999f)
// 			return (1);
// 	}
// 	return (0);
// }

// static void	lightdata(t_data *data, const t_vec3 hit, const t_light *l)
// {
// 	data->dist = fmaxf(powf(vec3_length(vec3_sub(hit, l->pos)) + 1.0f, 2.0f)
// 			- 1.0f, 2.0f);
// 	data->light = vec3_norm(vec3_sub(l->pos, hit));
// 	data->diffuse = clamp(vec3_dot(data->normal, data->light)
// 			/ data->dist, 0.0f, 1.0f);
// 	data->reflect = vec3_reflect(vec3_scale(data->light, -1.0f), data->normal);
// 	data->spec = powf(clamp(vec3_dot(data->view, data->reflect), 0.0f, 1.0f),
// 			32.0f) / data->dist;
// }

t_vec3	shade(t_obj *obj, t_vec3 hit, const t_scene *s, const t_vec3 ray)
{
	t_vec3	norm;
	t_vec3	light;
	t_vec3	color;
	t_hit	h;
	size_t	i;

	light = obj->emit;
	color = obj->color;
	norm = vec3_reflect(ray, randnorm(getnormal(obj, hit), obj->r));
	hit = vec3_add(hit, vec3_scale(norm, 0.00005f));
	i = -1;
	while (++i < SAMPLE_DEPTH)
	{
		h = raycast((t_ray){hit, norm}, s);
		if (!h.obj)
			break ;
		color = vec3_mult(color, h.obj->color);
		light = vec3_add(light, vec3_mult(vec3_scale(h.obj->emit, 4.0f),
					color));
		norm = vec3_reflect(norm, randnorm(getnormal(h.obj, h.pos), h.obj->r));
		hit = vec3_add(h.pos, vec3_scale(norm, 0.00005f));
	}
	return (light);
}
