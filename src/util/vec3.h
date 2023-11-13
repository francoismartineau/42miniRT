/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:44:23 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:20:44 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "def.h"

typedef struct s_vec3
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
		};
		float	e[3];
	};
}	t_vec3;

t_vec3	vec3_scale(const t_vec3 v, const float s);
t_vec3	vec3_mult(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_add(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_sub(const t_vec3 v1, const t_vec3 v2);
int		vec3_color(const t_vec3 v);

#endif
