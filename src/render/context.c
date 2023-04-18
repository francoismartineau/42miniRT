/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:06 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 07:43:08 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

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
