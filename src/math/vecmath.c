/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecmath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:38:39 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:25:26 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "util/vec3.h"

float	vec3_length(const t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_norm(const t_vec3 v)
{
	float	len;
	t_vec3	n;

	len = vec3_length(v);
	n.x = v.x / len;
	n.y = v.y / len;
	n.z = v.z / len;
	return (n);
}

float	vec3_dot(const t_vec3 v1, const t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_reflect(const t_vec3 v, const t_vec3 n)
{
	return (vec3_sub(v, vec3_scale(n, 2.0 * vec3_dot(n, v))));
}

t_vec3	vec3_cross(const t_vec3 v1, const t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
