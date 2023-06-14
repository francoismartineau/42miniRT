/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:04:34 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/05/31 13:16:28 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "shading.h"
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
	t_vec3	reflect;
	FPR		spec;
}	t_data;

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

static t_vec3	desaturate(const t_vec3 color, FPR total)
{
	const FPR		desat = powf(total, 5);

	return ((t_vec3){{{
				color.x + (1.0f - color.x) * desat,
				color.y + (1.0f - color.y) * desat,
				color.z + (1.0f - color.z) * desat,
			}}});
}

static int	isobscured(const t_vec3 hit, const t_scene *s,
	const t_obj *obj, const t_light *l)
{
	const t_ray		ray = (t_ray){l->pos, vec3_sub(hit, l->pos)};
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

static void	lightdata(t_data *data, const t_vec3 hit, const t_light *l)
{
	data->dist = fmaxf(powf(vec3_length(vec3_sub(hit, l->pos)) + 1.0f, 2.0f)
			- 1.0f, 2.0f);
	data->light = vec3_norm(vec3_sub(l->pos, hit));
	data->diffuse = clamp(vec3_dot(data->normal, data->light)
			/ data->dist, 0.0f, 1.0f);
	data->reflect = vec3_reflect(vec3_scale(data->light, -1.0f), data->normal);
	data->spec = powf(clamp(vec3_dot(data->view, data->reflect), 0.0f, 1.0f),
			32.0f) / data->dist;
}

t_vec3	shade(const t_obj *obj, const t_vec3 hit, const t_scene *s)
{
	t_data	data;
	t_vec3	color;
	size_t	i;

	color = s->a_light.color;
	i = -1;
	data.normal = getnormal(obj, hit);
	data.view = vec3_norm(vec3_sub(s->camera.pos, hit));
	while (++i < s->lightc)
	{
		if (isobscured(hit, s, obj, s->lights + i))
			continue ;
		lightdata(&data, hit, s->lights + i);
		color = vec3_add(color, desaturate(vec3_scale(vec3_mult(obj->color,
							s->lights[i].color), fminf(data.diffuse + data.spec,
							1.0f)), data.diffuse + data.spec));
	}
	return (color);
}
