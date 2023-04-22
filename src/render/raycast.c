/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:09:35 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/21 16:36:43 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/raycast.h"
#include "def.h"
#include "math/vecmath.h"
#include "math/mat3.h"

#include <math.h>

typedef struct s_quad
{
	FPR	a;
	FPR	b;
	FPR	c;
	FPR	d;
}	t_quad;

static FPR	ray_intersect_sphere(const t_ray ray, const t_sphere *obj)
{
	const t_vec3	oc = {{{ray.pos.x - obj->pos.x,
		ray.pos.y - obj->pos.y, ray.pos.z - obj->pos.z}}};
	const FPR		abc[3] = {
		vec3_dot(ray.dir, ray.dir),
		2 * vec3_dot(oc, ray.dir),
		vec3_dot(oc, oc) - obj->rad * obj->rad
	};
	const FPR		discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	FPR				t[2];

	if (discriminant < 0.0001)
		return (0.0);
	t[0] = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (t[0] > t[1])
		return (t[1]);
	return (t[0]);
}

FPR	ray_intersect_cylinder(t_ray ray, const t_cylinder *obj)
{
	// to consider the rotation of the cylinder
	// we need to rotate the ray by the inverse of the cylinder's rotation
	// matrix
	const t_mat3	rot = mat3_rotvec(obj->axis);
	const t_vec3	rot_ray_dir = mat3_mul_vec3(rot, ray.dir);
	const t_vec3	rot_ray_pos = mat3_mul_vec3(rot, ray.pos);
	const t_vec3	rot_obj_pos = mat3_mul_vec3(rot, obj->pos);
	const t_vec3	oc = {{{rot_ray_pos.x - rot_obj_pos.x,
		rot_ray_pos.y - rot_obj_pos.y, rot_ray_pos.z - rot_obj_pos.z}}};
	const t_quad	abcd = {
		.a = rot_ray_dir.x * rot_ray_dir.x + rot_ray_dir.z * rot_ray_dir.z,
		.b = 2 * (rot_ray_dir.x * oc.x + rot_ray_dir.z * oc.z),
		.c = oc.x * oc.x + oc.z * oc.z - obj->rad * obj->rad,
		.d = abcd.b * abcd.b - 4 * abcd.a * abcd.c
	};
	FPR				t[4];

	if (abcd.d < 0.0001)
		return (0.0);
	t[0] = (-abcd.b - sqrt(abcd.d)) / (2 * abcd.a);
	t[1] = (-abcd.b + sqrt(abcd.d)) / (2 * abcd.a);
	if (t[0] > t[1])
		t[2] = t[1];
	else
		t[2] = t[0];
	t[3] = rot_ray_pos.y + t[2] * rot_ray_dir.y;
	if (t[3] >= rot_obj_pos.y && t[3] <= rot_obj_pos.y + obj->height)
		return (t[2]);
	return (0.0);
	
	// const t_quad	abcd = {
	// 	.a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z,
	// 	.b = 2 * (ray.dir.x * (ray.pos.x - obj->pos.x)
	// 		+ ray.dir.z * (ray.pos.z - obj->pos.z)),
	// 	.c = (ray.pos.x - obj->pos.x) * (ray.pos.x - obj->pos.x)
	// 	+ (ray.pos.z - obj->pos.z) * (ray.pos.z - obj->pos.z)
	// 	- obj->rad * obj->rad,
	// 	.d = abcd.b * abcd.b - 4 * abcd.a * abcd.c
	// };
	// FPR				t[4];

	// if (abcd.d < 0.0001)
	// 	return (0.0);
	// t[0] = (-abcd.b - sqrt(abcd.d)) / (2 * abcd.a);
	// t[1] = (-abcd.b + sqrt(abcd.d)) / (2 * abcd.a);
	// if (t[0] > t[1])
	// 	t[2] = t[1];
	// else
	// 	t[2] = t[0];
	// t[3] = ray.pos.y + t[2] * ray.dir.y;
	// if (t[3] >= obj->pos.y && t[3] <= obj->pos.y + obj->height)
	// 	return (t[2]);
	// return (0.0);
}

// FPR	ray_intersect_plane(const t_ray ray, const t_plane *obj)
// {
// 	return (0.0);
// }

FPR	ray_intersect(t_ray ray, const t_obj *obj)
{
	if (obj->type == e_sphere)
		return (ray_intersect_sphere(ray, &obj->sphere));
	// else if (obj->type == e_plane)
	// 	return (ray_intersect_plane(ray, obj));
	else if (obj->type == e_cylinder)
	{
		// convert ray to cylinder space
		// ray.dir = mat3_mul_vec3(obj->cylinder.invrot, ray.dir);
		return (ray_intersect_cylinder(ray, &obj->cylinder));
	}
	return (0.0);
}
