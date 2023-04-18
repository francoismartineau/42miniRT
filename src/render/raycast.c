/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:09:35 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 15:22:24 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/raycast.h"
#include "def.h"
#include "math/vecmath.h"

#include <math.h>

static FPR	ray_intersect_sphere(const t_ray ray, const t_obj *obj)
{
	const t_vec3	oc = {{{ray.pos.x - obj->sphere.pos.x,
		ray.pos.y - obj->sphere.pos.y, ray.pos.z - obj->sphere.pos.z}}};
	const FPR		a = vec3_dot(ray.dir, ray.dir);
	const FPR		b = 2 * vec3_dot(oc, ray.dir);
	const FPR		c = vec3_dot(oc, oc) - obj->sphere.rad * obj->sphere.rad;
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

FPR	ray_intersect(const t_ray ray, const t_obj *obj)
{
	if (obj->type == e_sphere)
		return (ray_intersect_sphere(ray, obj));
	// else if (obj->type == e_plane)
	// 	return (ray_intersect_plane(ray, obj));
	// else if (obj->type == e_cylinder)
	// 	return (ray_intersect_cylinder(ray, obj));
	return (0.0);
}
