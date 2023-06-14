/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/14 14:21:37 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "math/vecmath.h"
#include "math/mat3.h"
#include "render/raycast.h"
#include "render/shading.h"
#include "thread.h"

#define SAMPLE_COUNT 64
#define SAMPLE_DEPTH 8

int	pixel_blend(const t_vec3 c1, int c2, size_t i)
{
	return (((((int)(c1.x * 255.0f) + (c2 >> 24)) / 2) << 24)
		| (((((int)(c1.y * 255.0f) + ((c2 >> 16) & 0xff))) / 2) << 16)
		| (((((int)(c1.z * 255.0f) + ((c2 >> 8) & 0xff))) / 2) << 8) | 0xff);
}

int	pixel_cast(t_context *ctx, const t_ray ray, const unsigned int x,
		const unsigned int y)
{
	t_vec3		color;
	t_hit		hit;

	hit = raycast(ray, &ctx->scene);
	hit = raycast((t_ray){{{{
			ray.pos.x + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
			ray.pos.y + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
			ray.pos.z + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
		}}}, ray.dir}, &ctx->scene);
	if (hit.obj)
		color = shade(hit.obj, hit.pos, &ctx->scene, SAMPLE_DEPTH);
	else
		color = (t_vec3){{{0.3f, 0.5f, 0.7f}}};
	color.x = sqrtf(color.x);
	color.y = sqrtf(color.y);
	color.z = sqrtf(color.z);
	return (pixel_blend(color, ctx->fb->pixels[y * ctx->width + x]));
}

void	renderregion(t_context *ctx, const t_region region)
{
	const FPR		fov = tanf(ctx->scene.camera.fov / 2.0f);
	unsigned int	i[3];

	i[2] = -1;
	while (++i[2] < SAMPLE_COUNT)
	{
		i[0] = region.y - 1;
		while (++i[0] < region.y + region.height && i[0] < ctx->height)
		{
			i[1] = region.x - 1;
			while (++i[1] < region.x + region.width && i[1] < ctx->width)
			{
				if (ctx->exit)
					return ;
				mlx_put_pixel(ctx->secimg[region.imgid], i[1] - region.x, i[0]
					- region.y, pixel_cast(ctx, (t_ray){ctx->scene.camera.pos,
						mat3_mul_vec3(ctx->scene.camera.rot, (t_vec3){{{
							(2.0f * ((i[1] + 0.5f) / ctx->width) - 1.0f)
							* ctx->aspect * fov, -(2.0f * ((i[0] + 0.5f)
									/ ctx->height) - 1.0f) * fov, 1.0f}}})
					}, i[1], i[0]));
			}
		}
		transferimg(ctx, &region);
	}
}

void	render(t_context *ctx)
{
	size_t		i;

	i = -1;
	while (++i < 6)
	{
		pthread_create(&ctx->threads[i], NULL, renderthread,
			(void *)ctx);
	}
}
