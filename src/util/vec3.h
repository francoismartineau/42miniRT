/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:44:23 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 08:07:19 by eboyce-n         ###   ########.fr       */
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
			FPR	x;
			FPR	y;
			FPR	z;
		};
		FPR	e[3];
	};
}	t_vec3;

// FPR		vec3_length(t_vec3 v);
// t_vec3	vec3_normalize(t_vec3 v);
FPR	vec3_dot(t_vec3 v1, t_vec3 v2);

#endif