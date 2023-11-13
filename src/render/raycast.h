/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:05:18 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:21:57 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "obj.h"
# include "util/vec3.h"
# include "context.h"

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}	t_ray;

typedef struct s_hit
{
	t_vec3	pos;
	t_obj	*obj;
}	t_hit;

float	ray_intersect(const t_ray ray, const t_obj *obj);
t_hit	raycast(const t_ray ray, const t_scene *s);

#endif
