/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/29 20:15:25 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include <stdio.h>
#include <math.h>

#include "math/vecmath.h"
#include "math/mat3.h"
#include "raycast.h"
#include "shading.h"

void	render(t_context *ctx)
{
	const FPR		fov = tanf(ctx->scene.camera.fov / 2.0f);
	t_hit			hit;
	unsigned int	i[2];

	i[0] = -1;
	while (++i[0] < ctx->height)
	{
		i[1] = -1;
		while (++i[1] < ctx->width)
		{
			hit = raycast((t_ray){ctx->scene.camera.pos,
					mat3_mul_vec3(ctx->scene.camera.rot, (t_vec3){{{
						(2.0f * ((i[1] + 0.5f) / ctx->width) - 1.0f)
						* ctx->aspect * fov,
						-(2.0f * ((i[0] + 0.5f) / ctx->height) - 1.0f) * fov,
						1.0f,
					}}})
				}, &ctx->scene);
			if (hit.obj)
				mlx_put_pixel(ctx->fb, i[1], i[0],
					shade(hit.obj, hit.pos, &ctx->scene));
			else
				mlx_put_pixel(ctx->fb, i[1], i[0], 0xff);
		}
	}
}
