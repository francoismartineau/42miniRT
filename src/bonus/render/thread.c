/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 22:26:02 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/14 14:22:59 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread.h"

#include "render/context.h"
#include "render/render.h"

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

void	transferimg(t_context *ctx, const t_region *region)
{
	const mlx_image_t	*img = ctx->secimg[region->imgid];
	size_t				i;
	size_t				j;

	i = 0;
	while (i < region->height && region->y + i < ctx->height)
	{
		j = 0;
		while (j < region->width && region->x + j < ctx->width)
		{
			((int *)ctx->fb->pixels)[(region->y + i)
				* ctx->width + region->x + j]
				= ((int *)img->pixels)[i * region->width + j];
			j++;
		}
		i++;
	}
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
		if (state->index * state->regionsize >= ctx->height * ctx->width)
			return ((void *)(size_t)pthread_mutex_unlock(&state->indexmutex));
		region = (t_region){state->index * state->regionsize % ctx->width,
			state->index * state->regionsize / ctx->width * state->regionsize,
			state->regionsize, state->regionsize, id};
		state->index++;
		pthread_mutex_unlock(&state->indexmutex);
		renderregion(ctx, region);
		transferimg(ctx, &region);
	}
	return (NULL);
}
