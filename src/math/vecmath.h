/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:36:17 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/04/18 14:03:19 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECMATH_H
# define VECMATH_H

# include "util/vec3.h"

FPR		vec3_length(const t_vec3 v);
FPR		vec3_dot(const t_vec3 v1, const t_vec3 v2);
t_vec3	vec3_normalize(const t_vec3 v);

#endif
