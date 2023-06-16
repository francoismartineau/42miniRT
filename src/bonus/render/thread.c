/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:26:02 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/16 13:41:24 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include "render/context.h"
#include "render/render.h"
#include "util/util.h"

#include <stdio.h>

t_rstate	*getstate(void)
{
	static t_rstate	state = {
		0,
		32,
		1,
		100,
		PTHREAD_MUTEX_INITIALIZER
	};

	return (&state);
}

int	vec_pixel(const t_vec3 *vec, float id)
{
	return (((int)(vec->x / id * 255.0f))
		| ((int)(vec->y / id * 255.0f) << 8)
		| ((int)(vec->z / id * 255.0f) << 16) | 0xFF000000);
}

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

void	transferimg(t_context *ctx, const t_region *region)
{
	const t_vec3	*img = ctx->secimg[region->imgid];
	size_t			i;
	size_t			j;

	i = 0;
	while (i < region->height)
	{
		j = 0;
		while (j < region->width)
		{
			((int *)ctx->fb->pixels)[(region->y + i)
				* ctx->width + region->x + j]
				= vec_pixel(img + (i * region->width + j),
					(float)ctx->frameid[region->imgid]);
			j++;
		}
		i++;
	}
	if (ctx->frameid[region->imgid] < SAMPLE_COUNT)
		renderbox(ctx, region);
	else
		printf("Rendered image %d\n", region->imgid);
	++(ctx->frameid[region->imgid]);
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
			id = state->index;
		if (state->index * state->regsize >= ctx->height * ctx->width)
			return ((void *)(size_t)pthread_mutex_unlock(&state->indexmutex));
		region = (t_region){state->index * state->regsize % ctx->width,
			state->index * state->regsize / ctx->width * state->regsize,
			state->regsize, state->regsize, id};
		if (region.y + region.height > ctx->height)
			region.height = ctx->height - region.y;
		if (region.x + region.width > ctx->width)
			region.width = ctx->width - region.x;
		state->index++;
		pthread_mutex_unlock(&state->indexmutex);
		ctx->frameid[id] = 1;
		ft_memset(ctx->secimg[id], 0, 12 * region.width * region.height);
		renderregion(ctx, region);
	}
	return (NULL);
}
