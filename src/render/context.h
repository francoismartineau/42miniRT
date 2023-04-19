/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:08 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 16:12:05 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <MLX42/MLX42.h>

typedef struct s_context
{
	int			width;
	int			height;
	mlx_t		*mlx;
	mlx_image_t	*fb;
	t_scene		scene;
}	t_context;

int		context_new(t_context *ctx, int width, int height);
void	context_free(t_context *ctx);

#endif
