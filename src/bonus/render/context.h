/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:36:08 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 07:28:48 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include "thread.h"

# include "MLX42/MLX42.h"
# include "obj.h"

typedef struct s_context
{
	unsigned int	width;
	unsigned int	height;
	FPR				aspect;
	mlx_t			*mlx;
	mlx_image_t		*fb;
	t_scene			scene;
	pthread_t		threads[THREADS];
	t_vec3			*secimg[THREADS];
	int				frameid[THREADS];
	int				exit;
}	t_context;

int		context_new(t_context *ctx, int width, int height);
void	context_free(t_context *ctx);

#endif
