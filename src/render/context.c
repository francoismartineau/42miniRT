/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 17:27:36 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

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
}

int	context_new(t_context *ctx, int width, int height)
{
	ctx->width = width;
	ctx->height = height;
	ctx->mlx = mlx_init(width, height, "miniRT", 1);
	ctx->fb = mlx_new_image(ctx->mlx, width, height);
	if (!ctx->mlx || !ctx->fb)
	{
		context_free(ctx);
		return (0);
	}
	ft_memset(ctx->fb->pixels, 255, width * height * 4);
	mlx_image_to_window(ctx->mlx, ctx->fb, 0, 0);
	mlx_resize_hook(ctx->mlx, &context_resize, ctx);
	return (1);
}

void	context_free(t_context *ctx)
{
	if (ctx->fb)
		mlx_delete_image(ctx->mlx, ctx->fb);
	if (ctx->mlx)
		mlx_terminate(ctx->mlx);
	ctx->fb = 0;
	ctx->mlx = 0;
}
