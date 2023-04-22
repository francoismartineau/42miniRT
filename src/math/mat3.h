/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:39 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/21 11:23:02 by eboyce-n         ###   ########.fr       */
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
			FPR	m00;
			FPR	m01;
			FPR	m02;
			FPR	m10;
			FPR	m11;
			FPR	m12;
			FPR	m20;
			FPR	m21;
			FPR	m22;
		};
		float	m[9];
	};
}	t_mat3;

t_mat3	mat3_rotvec(const t_vec3 v1);
t_vec3	mat3_mul_vec3(const t_mat3 m, const t_vec3 v);
t_mat3	mat3_inv(const t_mat3 m);

#endif
