/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/11/13 14:15:10 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "render/context.h"
#include "render/raycast.h"
#include "math/vecmath.h"
#include "exit.h"
#include "render/render.h"
#include "parse/parse.h"

#include <math.h>

void	rtkey(mlx_key_data_t keydata, void *param)
{
	t_context *const	ctx = (t_context *)param;

	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(ctx->mlx);
		}
	}
}

void	loop(void *param)
{
	static int			once = 0;
	t_context *const	ctx = (t_context *)param;

	if (once)
		return ;
	render(ctx);
	once = 1;
}

int	main(int argc, char const *argv[])
{
	t_context	ctx;

	if (argc != 2)
		exit_error(MSG_ARG_ERR);
	context_new(&ctx, 600, 450);
	if (parse_file(argv[1], &ctx.scene) == ERROR)
		exit_error(MSG_PARSE_ERR);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	mlx_key_hook(ctx.mlx, rtkey, &ctx);
	mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
