/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 11:34:41 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render/render.h"

#include <stdlib.h>
#include <stdio.h>

#include "math/vecmath.h"
#include "math/mat3.h"
#include "render/raycast.h"
#include "render/shading.h"
#include "thread.h"

#include <math.h>

static void	blend(t_vec3 *c1, const t_vec3 c2)
{
	*c1 = vec3_add(*c1, c2);
}

static t_vec3	*imgvec(t_context *ctx, const t_region *reg,
	const unsigned int x, const unsigned int y)
{
	return (&(ctx->secimg[reg->imgid][y * reg->width + x]));
}

t_vec3	pixel_cast(t_context *ctx, const t_ray ray,
	const unsigned int x, const unsigned int y)
{
	t_vec3		color;
	t_hit		hit;

	hit = raycast((t_ray){{{{
			ray.pos.x + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
			ray.pos.y + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
			ray.pos.z + ((rand() / (FPR)(RAND_MAX)) - 0.5f) * 0.0015f,
		}}}, ray.dir}, &ctx->scene);
	if (hit.obj)
		color = shade(hit.obj, hit.pos, &ctx->scene, ray.dir);
	else
		color = (t_vec3){{{0.3f, 0.5f, 0.8f}}};
	return (color);
}

void	renderregion(t_context *ctx, const t_region region)
{
	const FPR		fov = tanf(ctx->scene.camera.fov / 2.0f);
	unsigned int	i[3];

	i[2] = -1;
	while (++i[2] < SAMPLE_COUNT)
	{
		i[0] = region.y - 1;
		while (++i[0] < region.y + region.height)
		{
			i[1] = region.x - 1;
			while (++i[1] < region.x + region.width)
			{
				if (ctx->exit)
					return ;
				blend(imgvec(ctx, &region, i[1] - region.x, i[0] - region.y),
					pixel_cast(ctx, (t_ray){ctx->scene.camera.pos,
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
	// printf("threads: %d\n", THREADS);
	while (++i < THREADS)
		ctx->secimg[i] = malloc(getstate()->regsize * getstate()->regsize
				* sizeof(t_vec3));
	i = -1;
	while (++i < THREADS)
		pthread_create(&ctx->threads[i], NULL, renderthread,
			(void *)ctx);
}
