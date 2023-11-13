/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:39 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:19:40 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAT3_H
# define MAT3_H

# include "util/vec3.h"

typedef struct s_mat3
{
	union
	{
		struct
		{
			t_vec3		x;
			t_vec3		y;
			t_vec3		z;
		};
		struct
		{
			float	m00;
			float	m01;
			float	m02;
			float	m10;
			float	m11;
			float	m12;
			float	m20;
			float	m21;
			float	m22;
		};
		float	m[9];
	};
}	t_mat3;

t_mat3	mat3_rotvec(const t_vec3 v1);
t_vec3	mat3_mul_vec3(const t_mat3 m, const t_vec3 v);
t_mat3	mat3_inv(const t_mat3 m);
t_mat3	lookvector(const t_vec3 axis);

#endif
