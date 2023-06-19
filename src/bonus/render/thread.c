/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:26:02 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 10:24:08 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include "render/context.h"
#include "render/render.h"
#include "util/util.h"
#include "math/math.h"

#include <math.h>
#include <stdio.h>

t_rstate	*getstate(void)
{
	static t_rstate	state = {
		0,
		0,
		0,
		32,
		1,
		150,
		PTHREAD_MUTEX_INITIALIZER
	};

	return (&state);
}

t_region	nextregion(const t_context *ctx, size_t id)
{
	t_rstate *const	state = getstate();
	t_region		region;

	region.x = state->x;
	region.y = state->y;
	region.width = umin(state->regsize, ctx->width - region.x);
	region.height = umin(state->regsize, ctx->height - region.y);
	region.imgid = id;
	state->x += state->regsize;
	if (state->x >= ctx->width)
	{
		state->x = 0;
		state->y += state->regsize;
	}
	return (region);
}

// static int	vec_pixel(t_vec3 vec, float id)
// {
// 	return (imin((int)(vec.x / id * 255.0f), 255)
// 		| (imin((int)(vec.y / id * 255.0f), 255) << 8)
// 		| (imin((int)(vec.z / id * 255.0f), 255) << 16) | 0xFF000000);
// }

void	renderbox(t_context *ctx, const t_region *reg)
{
	int *const	img = (int *)ctx->fb->pixels;
	size_t		i;

	i = -1;
	while (++i < reg->height)
		if (i < reg->height / 4 || i > reg->height - reg->height / 4)
			img[(reg->y + i) * ctx->width + reg->x] = 0xFFFFFFFF;
	i = -1;
	while (++i < reg->height)
		if (i < reg->height / 4 || i > reg->height - reg->height / 4)
			img[(reg->y + i) * ctx->width + reg->x + reg->width - 1]
				= 0xFFFFFFFF;
	i = -1;
	while (++i < reg->width)
		if (i < reg->width / 4 || i > reg->width - reg->width / 4)
			img[reg->y * ctx->width + reg->x + i] = 0xFFFFFFFF;
	i = -1;
	while (++i < reg->width)
		if (i < reg->width / 4 || i > reg->width - reg->width / 4)
			img[(reg->y + reg->height - 1) * ctx->width
				+ reg->x + i] = 0xFFFFFFFF;
}

void	transferimg(t_context *ctx, const t_region *reg)
{
	const t_vec3	*img = ctx->secimg[reg->imgid];
	const t_vec3	*vec;
	float			id;
	size_t			i;
	size_t			j;

	i = 0;
	while (i < reg->height)
	{
		j = 0;
		while (j < reg->width)
		{
			vec = img + i * reg->width + j;
			id = (float)ctx->frameid[reg->imgid];
			((int *)ctx->fb->pixels)[(reg->y + i) * ctx->width + reg->x + j]
				= (imin((int)(sqrtf(vec->x / id) * 255.0f), 255)
					| (imin((int)(sqrtf(vec->y / id) * 255.0f), 255) << 8)
					| (imin((int)(sqrtf(vec->z / id) * 255.0f), 255) << 16)
					| 0xFF000000);
			j++;
		}
		i++;
	}
	if (ctx->frameid[reg->imgid]++ < SAMPLE_COUNT)
		renderbox(ctx, reg);
}

void	*renderthread(void *arg)
{
	t_rstate *const		state = getstate();
	t_context *const	ctx = arg;
	t_region			region;
	int					id;

	id = -1;
	while (1)
	{
		pthread_mutex_lock(&state->indexmutex);
		if (id == -1)
			id = state->threadindex++;
		if (state->y >= ctx->height)
			return ((void *)(size_t)pthread_mutex_unlock(&state->indexmutex));
		region = nextregion(ctx, id);
		pthread_mutex_unlock(&state->indexmutex);
		ctx->frameid[id] = 1;
		ft_memset(ctx->secimg[id], 0, 12 * region.width * region.height);
		renderregion(ctx, region);
	}
	return (NULL);
}
