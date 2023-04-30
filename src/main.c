/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/29 19:56:59 by eboyce-n         ###   ########.fr       */
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
#include "debug/debug.h"

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
		// ctx->scene.camera.ori = vec3_norm((t_vec3){{{0.5f * sinf(i / 15.0f), 0.5f * sinf(i / 12.0f), -1.0f}}});
		// ctx->scene.camera.rot = lookvector(ctx->scene.camera.ori);
		// ctx->scene.camera.fov = 0.5f * sinf(i / 10.0f) + 1.0f;
		// ctx->scene.camera.pos.z = 0.5f * sinf(i / 10.0f) + 0.5f;
		ctx->scene.lights[0].pos.x = 0.8f * sinf(i / 10.0f);
		ctx->scene.lights[0].pos.y = 0.6f * sinf(i / 7.0f) - 0.4f;
		ctx->scene.lights[0].pos.z = -0.5f * sinf(i / 13.0f) - 0.5f;
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
#ifdef DEBUG
	printf("DEBUG MODE\n");
	atexit(ft_exit);
#endif
	if (argc != 2)
		exit_error(MSG_ARG_ERR);
	context_new(&ctx, 800, 600);
	if (parse_file(argv[1], &ctx.scene) == ERROR)
		exit_error(MSG_PARSE_ERR);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	render(&ctx);
	mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
