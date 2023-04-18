/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:44:33 by francoma          #+#    #+#             */
/*   Updated: 2023/04/18 15:47:02 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "render/context.h"
#include "render/raycast.h"
#include "math/vecmath.h"
// #include "util/util.h"

	// parse_file("file.rt");

#include <math.h>

void	loop(void *param)
{
	const t_context	*ctx = param;
	static int		ii = 0;
	FPR				t;
	++ii;
	int				color;
	const t_obj		sph[3] = {{.type = e_sphere, .sphere = {.pos = {.x = 0, .y = 0.6, .z = -1.0}, .rad = 0.2, .colorv = {{{1.0, 0.1, 0.1}}}}},
		{.type = e_sphere, .sphere = {.pos = {.x = -0.3, .y = 0.1, .z = -1.2}, .rad = 0.3, .colorv = {{{0.1, 0.1, 1.0}}}}},
		{.type = e_sphere, .sphere = {.pos = {.x = 1, .y = -0.2, .z = -1.0}, .rad = 0.5, .colorv = {{{1.0, 1.0, 1.0}}}}}};
	const t_vec3	light = {{{0, 0, sin(ii * 0.1) * 1.0 - 0.5}}};
	const t_vec3	lcolor = {{{1, 1, 1}}};
	const t_vec3	ambient = {{{0.05, 0.05, 0.05}}};

	for (int i = 0; i < ctx->height; i++)
	{
		for (int j = 0; j < ctx->width; j++)
		{
			const t_ray	ray = {.pos = {{{sin(ii * 0.07) * 0.7, 0, 0}}},
				.dir = vec3_normalize((t_vec3){{{(FPR)j / ctx->height - 0.5, (FPR)i / ctx->height - 0.5, -0.6}}})};
			t = 0;
			int	k;
			t_vec3	hit;
			t_vec3	n;
			const t_sphere	*sphere;
			for(k = 0; k < 3 && !t; ++k)
			{
				const FPR t2 = ray_intersect(ray, &sph[k]);
				if (t2 > 0.0 && (t == 0.0 || t2 < t))
				{
					t = t2;
					hit = vec3_add(ray.pos, vec3_scale(ray.dir, t));
					n = vec3_normalize(vec3_sub(hit, sph[k].sphere.pos));
					sphere = &sph[k].sphere;
				}
			}
			if (t)
			{
				const t_vec3	light_dir = vec3_normalize(vec3_sub(light, hit));
				const FPR		diffuse = fmax(0.0, vec3_dot(light_dir, n));
				const t_vec3	diffuse_color = vec3_mult(vec3_scale(lcolor, diffuse), sphere->colorv);
				const t_vec3	colorv = vec3_add(vec3_scale(diffuse_color, 0.7), ambient);
				color = (int)(colorv.x * 255) << 24 | (int)(colorv.y * 255) << 16 | (int)(colorv.z * 255) << 8 | 0xFF;
			}
			else
				color = 0xff;
			mlx_put_pixel(ctx->fb, j, i, color);
		}
	}
}

int	main(int argc, char const *argv[])
{
	t_context	ctx;

	(void) argc;
	(void) argv;
	context_new(&ctx, 800, 600);
	mlx_loop_hook(ctx.mlx, loop, &ctx);
	mlx_loop(ctx.mlx);
	context_free(&ctx);
	return (0);
}
