/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:23:27 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/19 10:56:36 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "util/vec3.h"

t_vec3	vec3_scale(const t_vec3 v, const FPR s)
{
	t_vec3	vs;

	vs.x = v.x * s;
	vs.y = v.y * s;
	vs.z = v.z * s;
	return (vs);
}

t_vec3	vec3_mult(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec3	vec3_addf(const t_vec3 v, const FPR f)
{
	t_vec3	vf;

	vf.x = v.x + f;
	vf.y = v.y + f;
	vf.z = v.z + f;
	return (vf);
}

t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}
