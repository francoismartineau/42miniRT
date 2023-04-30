/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:55:09 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/29 15:38:14 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vecmath.h"
#include "mat3.h"

static t_mat3	rotation(const t_vec3 axis, const FPR angle)
{
	const t_vec3	axisn = vec3_norm(axis);
	const FPR		f[6] = {
		cosf(angle),
		sinf(angle),
		1.0f - f[0],
		axisn.x,
		axisn.y,
		axisn.z
	};
	const t_mat3	mat = {
		.x = {{{f[2] * f[3] * f[3] + f[0], f[2] * f[3] * f[4] - f[5] * f[1],
		f[2] * f[3] * f[5] + f[4] * f[1]}}},
		.y = {{{f[2] * f[4] * f[3] + f[5] * f[1], f[2] * f[4] * f[4] + f[0],
		f[2] * f[4] * f[5] - f[3] * f[1]}}},
		.z = {{{f[2] * f[5] * f[3] - f[4] * f[1], f[2] * f[5] * f[4] + f[3]
		* f[1], f[2] * f[5] * f[5] + f[0]}}}
	};

	return (mat);
}

t_mat3	mat3_rotvec(const t_vec3 v1)
{
	const t_vec3	up = {{{0.0f, -1.0f, 0.0f}}};
	const t_vec3	axis = vec3_cross(v1, up);
	const FPR		angle = acosf(vec3_dot(v1, up) / (vec3_length(v1)));

	return (rotation(axis, angle));
}

t_vec3	mat3_mul_vec3(const t_mat3 m, const t_vec3 v)
{
	t_vec3	v2;

	v2.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
	v2.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
	v2.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
	return (v2);
}

t_mat3	mat3_inv(const t_mat3 m)
{
	t_mat3	m2;

	m2.m00 = m.m11 * m.m22 - m.m12 * m.m21;
	m2.m01 = m.m02 * m.m21 - m.m01 * m.m22;
	m2.m02 = m.m01 * m.m12 - m.m02 * m.m11;
	m2.m10 = m.m12 * m.m20 - m.m10 * m.m22;
	m2.m11 = m.m00 * m.m22 - m.m02 * m.m20;
	m2.m12 = m.m02 * m.m10 - m.m00 * m.m12;
	m2.m20 = m.m10 * m.m21 - m.m11 * m.m20;
	m2.m21 = m.m01 * m.m20 - m.m00 * m.m21;
	m2.m22 = m.m00 * m.m11 - m.m01 * m.m10;
	return (m2);
}

t_mat3	lookvector(const t_vec3 axis)
{
	const t_vec3	up = {{{0.0f, -1.0f, 0.0f}}};
	const t_vec3	right = vec3_norm(vec3_cross(up, axis));
	const t_vec3	newup = vec3_norm(vec3_cross(axis, right));

	return ((t_mat3){{{
				{{{right.x, newup.x, axis.x}}},
				{{{right.y, newup.y, axis.y}}},
				{{{right.z, newup.z, axis.z}}}
			}}});
}
