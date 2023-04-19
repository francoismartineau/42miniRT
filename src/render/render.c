/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:56:57 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/19 09:19:35 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

#include "raycast.h"

typedef struct s_hit
{
	t_vec3		pos;
	const t_obj	*obj;
}	t_hit;

int	gethit(const t_ray ray, const t_scene *scene, t_hit *hit)
{
	unsigned int	i;
	FPR				t[2];

	i = -1;
	t[0] = 0;
	while (++i < scene->objc)
	{
		t[1] = ray_intersect(ray, &scene->objs[i]);
		if (t[1] > 0.0 && (t[0] == 0.0 || t[1] < t[0]))
		{
			t[0] = t[1];
			hit->obj = &scene->objs[i];
		}
	}
	if (t[0])
	{
		hit->pos = vec3_add(ray.pos, vec3_scale(ray.dir, t[0]));
		return (1);
	}
	return (0);
}

void	render(t_context *ctx)
{
	t_hit			hit;
	t_ray			ray;
	unsigned int	i[2];

	i[0] = -1;
	while (++i[0] < ctx->height)
	{
		i[1] = -1;
		while (++i[1] < ctx->width)
		{
			ray = (t_ray){.pos = ctx->scene.camera.pos,
				.dir = vec3_normalize((t_vec3){{{(FPR)i[1] / ctx->height - 0.5, (FPR)i[0] / ctx->height - 0.5, -0.6}}})};
			if (gethit(ray, &ctx->scene, &hit))
				mlx_put_pixel(ctx->fb, i[1], i[0], shade(hit.obj, hit.pos, ctx));
			else
				mlx_put_pixel(ctx->fb, i[1], i[0], 0xff);
		}
	}
}
