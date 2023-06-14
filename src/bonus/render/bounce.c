/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:20:08 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/05/29 20:44:11 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/raycast.h"
#include "render/shading.h"
#include "math/vecmath.h"

#include <stdlib.h>

t_vec3	avg_color(const t_vec3 *colors, size_t count)
{
	t_vec3	sum;
	size_t	i;

	sum = (t_vec3){{{0.0f, 0.0f, 0.0f}}};
	i = -1;
	while (++i < count)
		sum = vec3_add(sum, colors[i]);
	return (vec3_scale(sum, 1.0f / (FPR)count));
}
