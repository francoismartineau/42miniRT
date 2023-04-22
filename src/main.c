/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/22 11:30:21 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>

#include "render/context.h"
#include "render/raycast.h"
#include "math/vecmath.h"
#include "exit.h"
#include "render/render.h"
#include "parse/parse.h"

#include <math.h>

void	loop(void *param)
{
	static int	button = 0;
	static int	i = 0;
	t_context *const ctx = (t_context *)param;

	++i;
	if (mlx_is_key_down(((t_context *)param)->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(ctx->mlx);
		return ;
	}
	// if (mlx_is_key_down(ctx->mlx, MLX_KEY_SPACE) && !button)
	// {
		button = 1;
		ctx->scene.camera.pos.x = 0.5 * sin(i / 3.0);
		ctx->scene.lights[0].pos.x = 0.8 * sin(i / 10.0);
		ctx->scene.lights[0].pos.y = 0.8 * sin(i / 7.0);
		ctx->scene.lights[0].pos.z = -0.5 * sin(i / 13.0) - 0.5;
		ctx->scene.objs[0].sphere.pos.x = 0.8 * sin(i / 10.0);
		ctx->scene.objs[0].sphere.pos.y = 0.8 * sin(i / 7.0);
		ctx->scene.objs[0].sphere.pos.z = -0.5 * sin(i / 13.0) - 0.5;
		render(param);
	// }
	if (!mlx_is_key_down(ctx->mlx, MLX_KEY_SPACE))
		button = 0;
}

int	main(int argc, char const *argv[])
{
	t_context	ctx;

	(void) argc;
	(void) argv;
	if (argc != 2)
		exit_error(MSG_ARG_ERR);
	context_new(&ctx, 800, 600);
	if (parse_file(argv[1], &ctx.scene) == ERROR)
		exit(EXIT_FAILURE);
		exit_error(MSG_PARSE_ERR);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	render(&ctx);
	mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
