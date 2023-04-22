/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:55:09 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/21 16:28:55 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "vecmath.h"
#include "mat3.h"

t_mat3	mat3_new(const FPR f)
{
	const t_mat3	mat = {
		.x = {{{f, f, f}}},
		.y = {{{f, f, f}}},
		.z = {{{f, f, f}}}
	};

	return (mat);
}

static t_mat3	rotation(const t_vec3 axis, const FPR angle)
{
	const float		a = angle;
	const float		c = cos(a);
	const float		s = sin(a);
	const t_vec3	temp = vec3_scale(axis, 1.0f - c);
	t_mat3			mat;

	mat.m00 = c + temp.e[0] * axis.e[0];
	mat.m01 = temp.e[0] * axis.e[1] + s * axis.e[2];
	mat.m02 = temp.e[0] * axis.e[2] - s * axis.e[1];
	mat.m10 = temp.e[1] * axis.e[0] - s * axis.e[2];
	mat.m11 = c + temp.e[1] * axis.e[1];
	mat.m12 = temp.e[1] * axis.e[2] + s * axis.e[0];
	mat.m20 = temp.e[2] * axis.e[0] + s * axis.e[1];
	mat.m21 = temp.e[2] * axis.e[1] - s * axis.e[0];
	mat.m22 = c + temp.e[2] * axis.e[2];
	return (mat);
}

t_mat3	mat3_rotvec(const t_vec3 v1)
{
	const t_vec3	up = {{{0, -1, 0}}};
	const t_vec3	axis = vec3_cross(v1, up);
	const FPR		angle = acos(vec3_dot(v1, up) / (vec3_length(v1)));

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
