/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/05/10 17:59:46 by eboyce-n         ###   ########.fr       */
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

#define SAMPLE_COUNT 32
#define SAMPLE_DEPTH 8

int	pixel_cast(t_context *ctx, const t_ray ray, const unsigned int x,
		const unsigned int y)
{
	t_vec3		color;
	size_t		i;
	const float	scale = 1.0f / SAMPLE_COUNT;
	t_hit		hit;

	color = (t_vec3){{{0.0f, 0.0f, 0.0f}}};
	hit = raycast(ray, &ctx->scene);
	i = -1;
	while (++i < SAMPLE_COUNT)
	{
		hit = raycast((t_ray){{{{
				ray.pos.x + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
				ray.pos.y + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
				ray.pos.z + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
			}}}, ray.dir}, &ctx->scene);
		if (hit.obj)
			color = vec3_add(color, shade(hit.obj, hit.pos, &ctx->scene,
						SAMPLE_DEPTH));
		else
			color = vec3_add(color, (t_vec3){{{0.3f, 0.5f, 0.7f}}});
	}
	color.x = sqrtf(color.x * scale);
	color.y = sqrtf(color.y * scale);
	color.z = sqrtf(color.z * scale);
	return (vec3_color(color));
}

void	renderregion(t_context *ctx, const t_region region)
{
	const FPR		fov = tanf(ctx->scene.camera.fov / 2.0f);
	unsigned int	i[2];

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
						* ctx->aspect * fov,
						-(2.0f * ((i[0] + 0.5f) / ctx->height) - 1.0f) * fov,
						1.0f}}})
				}, i[1], i[0]));
		}
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
