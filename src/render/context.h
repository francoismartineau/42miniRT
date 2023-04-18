/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoma <francoma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:08 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 15:11:13 by francoma         ###   ########.fr       */
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

int		context_new(t_context *ctx, int width, int height, char const *path);
void	context_free(t_context *ctx);

#endif
