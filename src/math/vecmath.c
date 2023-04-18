/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecmath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:38:39 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 13:38:54 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "util/vec3.h"

static FPR	vec3_length(const t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	vec3_normalize(const t_vec3 v)
{
	FPR		len;
	t_vec3	n;

	len = vec3_length(v);
	n.x = v.x / len;
	n.y = v.y / len;
	n.z = v.z / len;
	return (n);
}
