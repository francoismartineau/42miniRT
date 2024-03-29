/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:36:17 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/11/09 16:25:20 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECMATH_H
# define VECMATH_H

# include "util/vec3.h"

float	vec3_length(const t_vec3 v);
float	vec3_dot(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_norm(const t_vec3 v);
t_vec3	vec3_reflect(const t_vec3 v, const t_vec3 n);
t_vec3	vec3_cross(const t_vec3 v1, const t_vec3 v2);

#endif
