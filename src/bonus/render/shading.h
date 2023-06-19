/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eboyce-n <eboyce-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 07:54:54 by eboyce-n          #+#    #+#             */
/*   Updated: 2023/06/19 11:34:12 by eboyce-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

# include "obj.h"
# include "render/context.h"
# include "render/raycast.h"

// t_vec3	bounce(const t_ray r, const t_scene *s, size_t d);
t_vec3	shade(t_obj *obj, t_vec3 hit, const t_scene *s, const t_vec3 ray);

#endif
