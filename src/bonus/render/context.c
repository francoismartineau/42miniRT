/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/16 10:17:26 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "context.h"
#include "parse/parse.h"
#include "render/render.h"
#include "render/thread.h"

#include "util/util.h"

static void	context_resize(int32_t width, int32_t height, void *param)
{
	t_context *const	ctx = (t_context *)param;
	mlx_image_t			*new_fb;

	new_fb = mlx_new_image(ctx->mlx, width, height);
	if (!new_fb)
		return ;
	mlx_delete_image(ctx->mlx, ctx->fb);
	ctx->fb = new_fb;
	mlx_image_to_window(ctx->mlx, ctx->fb, 0, 0);
	ctx->width = width;
	ctx->height = height;
	ctx->aspect = (FPR)width / (FPR)height;
	render(ctx);
}

int	context_new(t_context *ctx, int width, int height)
{
	size_t	i;

	ctx->width = width;
	ctx->height = height;
	ctx->aspect = (FPR)width / (FPR)height;
	ctx->mlx = mlx_init(width, height, "miniRT", 1);
	ctx->fb = mlx_new_image(ctx->mlx, width, height);
	i = -1;
	if (!ctx->mlx || !ctx->fb)
	{
		context_free(ctx);
		return (0);
	}
	ft_intset((int *)ctx->fb->pixels, 0xff000000, width * height);
	mlx_image_to_window(ctx->mlx, ctx->fb, 0, 0);
	mlx_resize_hook(ctx->mlx, &context_resize, ctx);
	return (1);
}

void	context_free(t_context *ctx)
{
	size_t	i;

	free_scene(&ctx->scene);
	if (ctx->fb)
		mlx_delete_image(ctx->mlx, ctx->fb);
	i = -1;
	while (++i < 6)
		free(ctx->secimg[i]);
	i = -1;
	if (ctx->mlx)
		mlx_terminate(ctx->mlx);
	ctx->fb = 0;
	ctx->mlx = 0;
}
