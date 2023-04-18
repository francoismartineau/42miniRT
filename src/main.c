/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 16:00:24 by francoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "render/context.h"
#include "render/raycast.h"
#include "parse/parse.h"
#include "util/util.h"
#include "exit.h"
#include "def.h"
// #include "util/util.h"

	// parse_file("file.rt");

void	loop(void *param)
{
	const t_context	*ctx = param;
	const t_obj		sph = {.type = e_sphere,
		.sphere = {.pos = {.x = 0, .y = 0, .z = 0.5}, .rad = 0.2}};
	const t_vec3	light = {{{0.5, 0.1, 0.1}}};

	for (int i = 0; i < ctx->height; i++)
	{
		for (int j = 0; j < ctx->width; j++)
		{
			const t_ray	ray = {.pos = {{{0, 0, 0}}},
				.dir = vec3_normalize((t_vec3){{{(FPR)j / ctx->height - 0.5, (FPR)i / ctx->height - 0.5, 1.0}}})};
			const FPR	t = ray_intersect(ray, &sph);
			const t_vec3	hit = vec3_add(ray.pos, vec3_scale(ray.dir, t));
			const t_vec3	norm = vec3_normalize(vec3_sub(hit, sph.sphere.pos));
			const int	color = (int)((norm.x + 1) * 0.5 * 255);
			mlx_put_pixel(ctx->fb, j, i, color << 16 | color << 8 | color << 24 | 0xFF);
		}
	}
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
		exit_error(MSG_PARSE_ERR);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
