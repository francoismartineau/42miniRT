/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:09:35 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/19 07:52:57 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/raycast.h"
#include "def.h"
#include "math/vecmath.h"

#include <math.h>

static FPR	ray_intersect_sphere(const t_ray ray, const t_sphere *obj)
{
	const t_vec3	oc = {{{ray.pos.x - obj->pos.x,
		ray.pos.y - obj->pos.y, ray.pos.z - obj->pos.z}}};
	const FPR		a = vec3_dot(ray.dir, ray.dir);
	const FPR		b = 2 * vec3_dot(oc, ray.dir);
	const FPR		c = vec3_dot(oc, oc) - obj->rad * obj->rad;
	const FPR		discriminant = b * b - 4 * a * c;
	FPR				t[2];

	if (discriminant < 0)
		return (0.0);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	if (t[0] > t[1])
		return t[1];
	return t[0];
}

FPR	ray_intersect_cylinder(const t_ray ray, const t_cylinder *obj)
{
	const FPR	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	const FPR	b = 2 * (ray.pos.x * ray.dir.x + ray.pos.z * ray.dir.z);
	const FPR	c = ray.pos.x * ray.pos.x + ray.pos.z * ray.pos.z - obj->rad * obj->rad;
	const FPR	discriminant = b * b - 4 * a * c;
	FPR			t[2];
	FPR			y[2];

	if (discriminant < 0)
		return (0.0);
	t[0] = (-b - sqrt(discriminant)) / (2 * a);
	t[1] = (-b + sqrt(discriminant)) / (2 * a);
	y[0] = ray.pos.y + t[0] * ray.dir.y;
	y[1] = ray.pos.y + t[1] * ray.dir.y;
	if (y[0] > obj->height || y[0] < 0)
		t[0] = -1;
	if (y[1] > obj->height || y[1] < 0)
		t[1] = -1;
	if (t[0] < 0 && t[1] < 0)
		return (0.0);
	if (t[0] > t[1])
		return t[1];
	return t[0];
}

// FPR	ray_intersect_plane(const t_ray ray, const t_plane *obj)
// {
// 	return (0.0);
// }

FPR	ray_intersect(const t_ray ray, const t_obj *obj)
{
	if (obj->type == e_sphere)
		return (ray_intersect_sphere(ray, &obj->sphere));
	// else if (obj->type == e_plane)
	// 	return (ray_intersect_plane(ray, obj));
	else if (obj->type == e_cylinder)
		return (ray_intersect_cylinder(ray, &obj->cylinder));
	return (0.0);
}
