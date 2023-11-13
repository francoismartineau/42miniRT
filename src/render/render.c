/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:19:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "math/vecmath.h"
#include "math/mat3.h"
#include "raycast.h"
#include "shading.h"

void	renderregion(t_context *ctx, const t_region region)
{
	const float		fov = tanf(ctx->scene.camera.fov / 2.0f);
	t_hit			hit;
	unsigned int	i[2];

	i[0] = region.y - 1;
	while (++i[0] < region.y + region.height && i[0] < ctx->height)
	{
		i[1] = region.x - 1;
		while (++i[1] < region.x + region.width && i[1] < ctx->width)
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
					vec3_color(shade(hit.obj, hit.pos, &ctx->scene)));
			else
				mlx_put_pixel(ctx->fb, i[1], i[0], 0xff);
		}
	}
}

void	render(t_context *ctx)
{
	const time_t	start = time(NULL);

	renderregion(ctx, (t_region){0, 0, ctx->width, ctx->height});
	printf("Render time: %lds\n", time(NULL) - start);
}
